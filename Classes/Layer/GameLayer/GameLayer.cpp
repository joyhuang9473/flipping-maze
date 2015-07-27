#include "GameLayer.h"
#include "VisibleRect.h"
#include "../../GameManager.h"
#include "../../Controller/KeyboardController.h"
#include "../../Scene/GameScene.h"

USING_NS_CC;

#define PTM_RATIO 32
#define GAMEMANAGER GameManager::getInstance()
#define WINSIZE Director::getInstance()->getVisibleSize()

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
	map->setContentSize(map->getContentSize() * map->getScale());
	map->setTileSize(map->getTileSize() * map->getScale());
	//map->ignoreAnchorPointForPosition(false);
	//map->setAnchorPoint(Vec2(0, map->getContentSize()));

	this->setListener();

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

bool GameLayer::onTouchBegan(Touch* touch, Event* event) {
	return true;
}

void GameLayer::onTouchMoved(Touch* touch, Event* event) {
	Vec2 touchLocation = this->convertTouchToNodeSpace(touch);
	Vec2 oldTouchLocation = touch->getPreviousLocation();

	oldTouchLocation = this->convertToNodeSpace(oldTouchLocation);

	Vec2 translation = touchLocation - oldTouchLocation;
	this->panForTranslation(translation);
}

void GameLayer::onTouchEnded(Touch* touch, Event* event) {

}

void GameLayer::setListener() {
	this->m_touchListener = EventListenerTouchOneByOne::create();
	this->m_touchListener->setSwallowTouches(true);
	this->m_touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	this->m_touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->m_touchListener, this);
}

Vec2 GameLayer::boundLayerPos(Vec2 newPos) {
	Vec2 retval = newPos;

	retval.x = MIN(retval.x, 0);
	retval.x = MAX(retval.x, -this->m_map->getContentSize().width + WINSIZE.width);
	retval.y = MIN(retval.y, 0);
	retval.y = MAX(retval.y, -this->m_map->getContentSize().height + WINSIZE.height);

	return retval;
}

void GameLayer::panForTranslation(Vec2 translation) {
	Vec2 newPos = this->getPosition() + translation;

	this->setPosition(this->boundLayerPos(newPos));
}
