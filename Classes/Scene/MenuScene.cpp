#include "MenuScene.h"
#include "../Layer/MenuLayer/MenuLayer.h"

USING_NS_CC;

bool MenuScene::init() {
    if (!Scene::init()) {
        return false;
    }

    this->addChild(MenuLayer::create());
    return true;
}
