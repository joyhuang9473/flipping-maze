#include "GameLayer.h"
#include "VisibleRect.h"
#include "Box2D/Box2D.h"
#include "GameManager.h"
#include "../../Controller/KeyboardController.h"
#include "../../Scene/GameScene.h"

USING_NS_CC;

#define PTM_RATIO 32
#define GAMEMANAGER GameManager::getInstance()

bool GameLayer::init() {
    if( ! Layer::init() ) {
        return false;
    }

    this->initPhysics();

    // Stage
    auto stageFile = GAMEMANAGER->getCurStageFile();
    if (stageFile == "") {
        stageFile = "default.plist";
    }

    GAMEMANAGER->readStageInfo(stageFile);
    this->isMissionComplete = false;
    this->isInterrupted = false;

    // Map
    auto map = TMXTiledMap::create(GAMEMANAGER->getCurMapName());

    // Player
	auto player = Player::create();

	this->setPlayer(map, player);

    this->schedule(schedule_selector(GameLayer::logic));
    this->schedule(schedule_selector(GameLayer::updateActionScope));
    this->schedule(schedule_selector(GameLayer::updateBoxBody));
    return true;
}

void GameLayer::initPhysics() {
    b2Vec2 gravity;
    gravity.Set(0.0f, 0.0f);
    
    this->m_world = new b2World(gravity);
    this->m_world->SetAllowSleeping(false);
    
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);
    
    b2Body* groundBody = this->m_world->CreateBody(&groundBodyDef);
    b2EdgeShape groundBox;
    
    // bottom
    groundBox.Set(b2Vec2(VisibleRect::leftBottom().x / PTM_RATIO, VisibleRect::leftBottom().y / PTM_RATIO),
                  b2Vec2(VisibleRect::rightBottom().x / PTM_RATIO, VisibleRect::rightBottom().y / PTM_RATIO));
    groundBody->CreateFixture(&groundBox, 0);
    
    // right
    groundBox.Set(b2Vec2(VisibleRect::rightBottom().x / PTM_RATIO, VisibleRect::rightBottom().y / PTM_RATIO),
                  b2Vec2(VisibleRect::rightTop().x / PTM_RATIO, VisibleRect::rightTop().y / PTM_RATIO));
    groundBody->CreateFixture(&groundBox, 0);
    
    // top
    groundBox.Set(b2Vec2(VisibleRect::leftTop().x / PTM_RATIO, VisibleRect::leftTop().y / PTM_RATIO),
                  b2Vec2(VisibleRect::rightTop().x / PTM_RATIO, VisibleRect::rightTop().y / PTM_RATIO));
    groundBody->CreateFixture(&groundBox, 0);
    
    // left
    groundBox.Set(b2Vec2(VisibleRect::leftBottom().x / PTM_RATIO, VisibleRect::leftBottom().y / PTM_RATIO),
                  b2Vec2(VisibleRect::leftTop().x / PTM_RATIO, VisibleRect::leftTop().y / PTM_RATIO));
    groundBody->CreateFixture(&groundBox, 0);
    
    this->m_contactListener = new ContactListener();
    this->m_world->SetContactListener(this->m_contactListener);
}

void GameLayer::setPlayer(TMXTiledMap* map, Player* player) {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	KeyboardController* keyboardController = KeyboardController::create();
	keyboardController->registerWithKeyboardDispatcher();
	keyboardController->setRole(player);

	player->setTiledMap(map);
	player->setController(keyboardController);
	player->addChild(keyboardController);
	player->getFSM()->doEvent("stand");
	player->setPosition(visibleSize.width/2, visibleSize.height/2);

	this->addBoxBodyForRole(player);

	this->m_map = map;
	this->m_player = player;

	this->addChild(this->m_map, -1);
	this->addChild(this->m_player);
}

bool GameLayer::collisionDetection(const BoundingBox &hitBox, const BoundingBox &bodyBox) {
    Rect hitRect = hitBox.actual;
    Rect bodyRect = bodyBox.actual;

    if (hitRect.intersectsRect(bodyRect)) {
        return true;
    }
    return false;
}

void GameLayer::addBoxBodyForRole(Role* role) {
	/*
	** It should be adjsuted
	*/
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(role->getPositionX() / PTM_RATIO, role->getPositionY() / PTM_RATIO);
    bodyDef.userData = role;

    b2Body* body = this->m_world->CreateBody(&bodyDef);
    int num = 5;
    b2Vec2 verts[] = {
        b2Vec2(-39.0f / PTM_RATIO, 39.0f / PTM_RATIO),
        b2Vec2(39.0f / PTM_RATIO, 39.0f / PTM_RATIO),
        b2Vec2(39.0f / PTM_RATIO, -39.0f / PTM_RATIO),
        b2Vec2(-39.0f / PTM_RATIO, -39.0f / PTM_RATIO),
        b2Vec2(-39.0f / PTM_RATIO, 39.0f / PTM_RATIO),
    };

    b2FixtureDef fixtureDef;
    b2PolygonShape spriteShape;
    spriteShape.Set(verts, num);
    fixtureDef.shape = &spriteShape;
    fixtureDef.density = 10.0f;
    fixtureDef.isSensor = true;

    body->CreateFixture(&fixtureDef);
}

void GameLayer::logic(float dt) {
    if (this->isInterrupted) {
        return;
    }
    if (this->m_player->getFSM()->getCurrState() == "dead") {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("missionFailed");
        this->isInterrupted = true;
        return;
    }
    if (this->isMissionComplete) {
        auto nextStageFile = GAMEMANAGER->getNextStageFile();

        if (nextStageFile != "") {
            GAMEMANAGER->setCurStageFile(nextStageFile);
            Director::getInstance()->replaceScene(GameScene::create());
        } else {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("missionComplete");
        }
        this->isInterrupted = true;
        return;
    }

	//this->isMissionComplete = true;
}

void GameLayer::updateActionScope(float dt) {
    auto visibleSize = Size(this->m_map->getMapSize().width * this->m_map->getTileSize().width,
                            this->m_map->getMapSize().height * this->m_map->getTileSize().height);

    for (b2Body* body = this->m_world->GetBodyList() ; body ; body = body->GetNext()) {
        if (body->GetUserData() != NULL) {
            Role* role = (Role*)body->GetUserData();
            Size spriteSize = role->getSprite()->getDisplayFrame()->getRect().size;
            Point pos = role->getTagPosition();

            pos.x = (pos.x < visibleSize.width - spriteSize.width) ? pos.x : visibleSize.width - spriteSize.width;
            pos.x = (pos.x > spriteSize.width) ? pos.x : spriteSize.width;
            pos.y = (pos.y < visibleSize.height - spriteSize.height) ? pos.y : visibleSize.height - spriteSize.height;
            pos.y = (pos.y > spriteSize.height) ? pos.y : spriteSize.height;

            role->setTagPosition(pos.x, pos.y);
        }
    }
}

void GameLayer::updateBoxBody(float dt) {
    this->m_world->Step(dt, 10, 10);

    std::vector<b2Body*> toDestroy;

    // check all body in physics world
    for (b2Body* body = this->m_world->GetBodyList() ; body ; body = body->GetNext()) {
        if (body->GetUserData() != NULL) {
            Role* role = (Role*)body->GetUserData();

            // update boxbody
            body->SetTransform(b2Vec2(role->getTagPosition().x / PTM_RATIO, role->getTagPosition().y / PTM_RATIO), 0);

            if (role->getFSM()->getCurrState() == "dead") {
                role->removeChild(role->getController());

                //toDestroy.push_back(body);
            }
        }
    }

    std::vector<Contact>::iterator iter;
    for (iter = this->m_contactListener->m_contacts.begin() ; iter != this->m_contactListener->m_contacts.end() ; ++iter) {
        Contact contact = *(iter);
        b2Body* bodyA = contact.fixtureA->GetBody();
        b2Body* bodyB = contact.fixtureB->GetBody();

        if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
            Role* roleA = (Role*)bodyA->GetUserData();
            Role* roleB = (Role*)bodyB->GetUserData();

			// some interactions
        }
    }

    // remove dead role
    std::vector<b2Body*>::iterator iter2;
    for (iter2 = toDestroy.begin() ; iter2 != toDestroy.end() ; ++iter2) {
        b2Body* body = *(iter2);

        if (body->GetUserData() != NULL) {
            Role* role = (Role*)body->GetUserData();
            this->removeChild(role);
        }
        this->m_world->DestroyBody(body);
    }

}
