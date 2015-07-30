#include "GameLayer.h"
#include "VisibleRect.h"
#include "GroupEnemy.h"
#include "GroupPath.h"
#include "../../GameManager.h"
#include "../../Controller/KeyboardController.h"
#include "../../Scene/GameScene.h"

#include "../../Entity/Role/Enemy.h"
#include "../../Controller/PathController.h"

USING_NS_CC;

#define PTM_RATIO 32
#define GAMEMANAGER GameManager::getInstance()
#define WINSIZE Director::getInstance()->getVisibleSize()

bool GameLayer::init() {
    if( ! Layer::init() ) {
        return false;
    }

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

    this->m_map = map;

    this->setListener();

    // Enemy
    this->addEnemyWave();

    this->addChild(this->m_map, -1);
    this->schedule(schedule_selector(GameLayer::logic));
    return true;
}

void GameLayer::logic(float dt) {
    if (GAMEMANAGER->isMissionComplete()) {
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("missionComplete");
    } else if (GAMEMANAGER->isMissionFailed()) {
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("missionFailed");
    }

    if (!GAMEMANAGER->isFinishedAddWaves() && this->m_waitTime <= 0) {
    	//this->addEnemyWave();
    } else {
    	--this->m_waitTime;
    }
}

void GameLayer::initPhysics() {
    this->m_world->setGravity(Vec2(0.0, -45.0));

    /*
    * Bounding: block
    */
    auto blockLayer = this->m_map->getLayer("blocks");

    for (int x = 0; x < this->m_map->getMapSize().width; x++) {
        for (int y = 0; y < this->m_map->getMapSize().height; y++) {
            int gid = blockLayer->getTileGIDAt(Vec2(x,y));

            if (gid != 0) {
                Sprite* sprite = blockLayer->getTileAt(Vec2(x, y));

                if (!sprite) {
                    continue;
                }

                PhysicsBody* body = PhysicsBody::createEdgeBox(sprite->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
                body->setContactTestBitmask(0xFFFFFFFF);
                sprite->setPhysicsBody(body);
                sprite->setPosition(sprite->getPosition() + sprite->getContentSize()/2);
            }
        }
    }
}

void GameLayer::updatePhysicsBody(float dt) {}

void GameLayer::updateActionScope(float dt) {}

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

void GameLayer::onTouchEnded(Touch* touch, Event* event) {}

void GameLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    TMXObjectGroup* weaponObject = this->m_map->getObjectGroup("weapon");
    ValueMap posMap;

    switch (keyCode) {
        // Direction
        case EventKeyboard::KeyCode::KEY_1:
            posMap = weaponObject->getObject("1");
            this->addBall(Vec2(posMap["x"].asFloat() * this->m_map->getScale(), posMap["y"].asFloat() * this->m_map->getScale()));
            break;
        case EventKeyboard::KeyCode::KEY_2:
            posMap = weaponObject->getObject("2");
            this->addBall(Vec2(posMap["x"].asFloat() * this->m_map->getScale(), posMap["y"].asFloat() * this->m_map->getScale()));
            break;
        case EventKeyboard::KeyCode::KEY_3:
            posMap = weaponObject->getObject("3");
            this->addBall(Vec2(posMap["x"].asFloat() * this->m_map->getScale(), posMap["y"].asFloat() * this->m_map->getScale()));
            break;
        case EventKeyboard::KeyCode::KEY_4:
            posMap = weaponObject->getObject("4");
            this->addBall(Vec2(posMap["x"].asFloat() * this->m_map->getScale(), posMap["y"].asFloat() * this->m_map->getScale()));
            break;
        default:
            ;
    }
}

void GameLayer::setListener() {
    this->m_touchListener = EventListenerTouchOneByOne::create();
    this->m_touchListener->setSwallowTouches(true);
    this->m_touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    this->m_touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);

    this->m_keyboardListener = EventListenerKeyboard::create();
    this->m_keyboardListener->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->m_touchListener, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->m_keyboardListener, this);
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

void GameLayer::setPhysicsWorld(PhysicsWorld* world) {
    this->m_world = world;
}

Vec2 GameLayer::mapTileCoordToPos(Vec2 coord) {
    int x = coord.x * this->m_map->getTileSize().width * this->m_map->getScale();
    int y = (this->m_map->getMapSize().height - coord.y) * this->m_map->getTileSize().height;
    return Vec2(x, y);
}

void GameLayer::addBall(Vec2 position) {
    auto ball = Sprite::create("soccerBall.png");
    auto boundBody = PhysicsBody::createBox(ball->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    ball->setPhysicsBody(boundBody);
    ball->setPosition(position);

    this->addChild(ball);
}

void GameLayer::addEnemyWave() {
    int enemyWaveCounter = GAMEMANAGER->getEnemyWaveCounter();

	GroupPath* wave = GAMEMANAGER->getWaveVector().at(enemyWaveCounter);
	Vector<GroupEnemy*> wavePaths = wave->getPaths();

	for (int i = 0; i < wavePaths.size(); ++i) {
		GroupEnemy* groupEnemy = wavePaths.at(i);

		// Path points
		int initPointCounter = 0;
		TMXObjectGroup* pathObjectGroup = this->m_map->getObjectGroup(StringUtils::format("path%d", i));
		auto pointObjects = pathObjectGroup->getObjects();
		std::vector<Vec2> pathPoints;

		for (auto iter = pointObjects.begin(); iter != pointObjects.end(); ++iter) {
			ValueMap& pointDict = iter->asValueMap();
			pathPoints.push_back(Vec2(pointDict["x"].asFloat() * this->m_map->getScale(), pointDict["y"].asFloat() * this->m_map->getScale()));
			++initPointCounter;
		}

		// Enemy entities
		for (int i = 0; i < groupEnemy->getEnemyTotal(); i++) {
			Enemy* enemy = Enemy::create();

			enemy->setTiledMap(this->m_map);
			enemy->setPosition(pathPoints.at(0));
			enemy->setWithPhysics();
			enemy->getFSM()->doEvent("stand");

			PathController* controller = PathController::create();
			controller->setRole(enemy);
			controller->setPathPoints(pathPoints);

			enemy->setController(controller);
			enemy->addChild(controller);
			this->addChild(enemy);
		}
	}

    ++enemyWaveCounter;
    GAMEMANAGER->setEnemyWaveCounter(enemyWaveCounter);
}
