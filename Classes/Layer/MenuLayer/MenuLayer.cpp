#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
#include "../../Scene/GameScene.h"

USING_NS_CC;
using namespace CocosDenshion;

bool MenuLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    // Audio
    //SimpleAudioEngine::getInstance()->playBackgroundMusic("file_name.mp3", true);

    // Background
    this->setBackground();

    // Menu
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vector<MenuItem*> MenuItems;

    auto startItem = MenuItemImage::create("signStart.png",
                                           "signStartEnable.png",
                                           CC_CALLBACK_0(MenuLayer::menuStartCallback, this));

    auto closeItem = MenuItemImage::create("signExit.png",
                                           "signExitEnable.png",
                                           CC_CALLBACK_1(MenuLayer::menuCloseCallback, this));

    startItem->setPosition(Vec2(origin.x + visibleSize.width/2 - startItem->getContentSize().width, origin.y + visibleSize.height/3));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width/2 + closeItem->getContentSize().width, origin.y + visibleSize.height/3));

    MenuItems.pushBack(startItem);
    MenuItems.pushBack(closeItem);

    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("Hackathon Application Demo", "Marker Felt.ttf", 72);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - 2*label->getContentSize().height));
    this->addChild(label, 1);

    this->scheduleUpdate();
    return true;
}

void MenuLayer::menuStartCallback() {
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(GameScene::create());
}

void MenuLayer::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MenuLayer::setBackground() {

}

void MenuLayer::update(float dt) {

}
