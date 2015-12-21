#include "GameManager.h"

USING_NS_CC;

GameManager* GameManager::instance;

GameManager::GameManager() {
	std::vector<std::string> resourcePathes;

	resourcePathes.push_back("Audio");
	resourcePathes.push_back("Button");
	resourcePathes.push_back("Character");
	resourcePathes.push_back("Font");
	resourcePathes.push_back("Map");
	resourcePathes.push_back("Setting");
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

    this->setCurStageFile(this->stageInfo["curStage"].asString());
    this->setNextStageFile(this->stageInfo["nextStage"].asString());
    this->setCurMapName(this->resources["map"].asString());
    //this->setCurBgName(this->resources["image"].asString());
}

void GameManager::clear() {
    this->resources.clear();
    this->stageInfo.clear();
}
