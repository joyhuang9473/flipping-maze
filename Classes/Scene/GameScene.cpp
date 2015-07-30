#include "GameScene.h"
#include "../Layer/GameLayer/GameLayer.h"

USING_NS_CC;

bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }

    Director::getInstance()->getEventDispatcher()->addCustomEventListener("missionComplete", CC_CALLBACK_0(GameScene::createCompleteDialog, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("missionFailed", CC_CALLBACK_0(GameScene::createFailedDialog, this));

    this->addChild(GameLayer::create());
    return true;
}

Scene* GameScene::createWithPhysicsWorld() {
	auto scene = GameScene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = GameLayer::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	layer->initPhysics();

	scene->addChild(layer);
	return scene;
}

void GameScene::createCompleteDialog() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto label = Label::createWithTTF("Mission Complete", "Marker Felt.ttf", 72);

    label->setPosition(Vec2(visibleSize.width/2, 2*visibleSize.height/3));
    this->addChild(label);
}

void GameScene::createFailedDialog() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto label = Label::createWithTTF("Mission Failed", "Marker Felt.ttf", 72);

    label->setPosition(Vec2(visibleSize.width/2, 2*visibleSize.height/3));
    this->addChild(label);
}

void GameScene::menuCallback() {

}
