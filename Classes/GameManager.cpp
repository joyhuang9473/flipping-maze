#include "GameManager.h"
#include "Layer/GameLayer/GroupEnemy.h"

USING_NS_CC;

GameManager* GameManager::instance;

GameManager::GameManager() {
	std::vector<std::string> resourcePathes;

	resourcePathes.push_back("Audio");
	resourcePathes.push_back("Buttons");
	resourcePathes.push_back("Characters");
	resourcePathes.push_back("Fonts");
	resourcePathes.push_back("Map");
	resourcePathes.push_back("Settings");
	resourcePathes.push_back("Other");

	FileUtils::getInstance()->setSearchPaths(resourcePathes);
}

GameManager::~GameManager() {}

GameManager* GameManager::getInstance() {
    if (instance == nullptr) {
        instance = new GameManager();
    }

    return instance;
}

void GameManager::readStageInfo(const std::string plistpath) {
    this->clear();

    do {
        ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(plistpath.c_str());
        this->resources = dict["resources"].asValueMap();
        this->stageInfo = dict["stageInfo"].asValueMap();
    } while (0);

	// Resource
	this->setCurMapName(this->resources["map"].asString());

	// StageInfo
    this->setCurStageFile(this->stageInfo["curStage"].asString());
    this->setNextStageFile(this->stageInfo["nextStage"].asString());
    this->setPlayerLife(this->stageInfo["playerLife"].asInt());

    ValueMap& waveDict = this->stageInfo["wave"].asValueMap();

	for (auto waveIter = waveDict.begin(); waveIter != waveDict.end(); ++waveIter) {
		ValueMap& waveDict = waveIter->second.asValueMap();
		ValueMap& wavePathDict = waveDict["path"].asValueMap();
		Vector<GroupEnemy*> wavePaths;

		for (auto wavePathIter = wavePathDict.begin(); wavePathIter != wavePathDict.end(); ++wavePathIter) {
			ValueMap& wavePathDict = wavePathIter->second.asValueMap();
			auto type1Num = wavePathDict["type1Num"].asInt();
			auto type2Num = wavePathDict["type2Num"].asInt();
			auto type1Hp = wavePathDict["type1Hp"].asInt();
			auto type2Hp = wavePathDict["type2Hp"].asInt();

			GroupEnemy* groupEnemy = GroupEnemy::create()->initGroupEnemy(type1Num, type1Hp, type2Num, type2Hp);
			wavePaths.pushBack(groupEnemy);

			this->numsOfEnemy += type1Num + type2Num;
		}

		GroupPath* groupPath = GroupPath::create()->initGroupPath(wavePaths, waveDict["waitTime"].asInt());
		this->waveVector.pushBack(groupPath);
	}

}

void GameManager::clear() {
	this->waveVector.clear();
    this->resources.clear();
    this->stageInfo.clear();

    this->enemyWaveCounter = 0;
    this->numsOfEnemy = 0;
    this->playerLife = 0;
}

bool GameManager::isFinishedAddWaves() {
    if (this->enemyWaveCounter >= this->waveVector.size()) {
        return true;
    }

    return false;
}

bool GameManager::isMissionComplete() {
    if (this->isFinishedAddWaves() && this->numsOfEnemy == 0) {
        return true;
    }

    return true;
}

bool GameManager::isMissionFailed() {
    if (this->playerLife <= 0) {
        return true;
    }

    return false;
}
