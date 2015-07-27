#include "GameLayer.h"
#include "VisibleRect.h"
#include "../../GameManager.h"
#include "../../Controller/KeyboardController.h"
#include "../../Scene/GameScene.h"

USING_NS_CC;

#define PTM_RATIO 32
#define GAMEMANAGER GameManager::getInstance()

bool GameLayer::init() {
    if( ! Layer::init() ) {
        return false;
    }

	// Physics World
    //this->initPhysics();

    // Stage
    auto stageFile = GAMEMANAGER->getCurStageFile();
    if (stageFile == "") {
        stageFile = "default.plist";
    }

    GAMEMANAGER->readStageInfo(stageFile);

    // Map
    auto map = TMXTiledMap::create(GAMEMANAGER->getCurMapName());
	map->setScale(2);
	map->setTileSize(map->getTileSize()*2);

	this->m_map = map;
	this->addChild(this->m_map, -1);

    this->schedule(schedule_selector(GameLayer::logic));
    return true;
}

/*
void GameLayer::setPlayer(Player* player) {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	KeyboardController* keyboardController = KeyboardController::create();
	keyboardController->registerWithKeyboardDispatcher();
	keyboardController->setRole(player);

	player->setController(keyboardController);
	player->addChild(keyboardController);
	player->getFSM()->doEvent("stand");
	player->setPosition(visibleSize.width / 2, visibleSize.height / 2);
}
*/

/*
void GameLayer::bindRoleToMap(Role* role, cocos2d::TMXTiledMap* map) {
	role->setTiledMap(map);
}
*/

void GameLayer::logic(float dt) {

	/*
	* Mission Complete
	*/
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("missionComplete");

	/*
	* Mission Failed
	*/
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("missionFailed");

}

void GameLayer::initPhysics() {

}

void GameLayer::setPhysicsBodyForRole(Role* role) {

}

void GameLayer::updatePhysicsBody(float dt) {

}

void GameLayer::updateActionScope(float dt) {

}

bool GameLayer::collisionDetection(const BoundingBox &bodyBoxA, const BoundingBox &bodyBoxB) {
	return true;
}
