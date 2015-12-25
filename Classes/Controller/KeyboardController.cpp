#include "KeyboardController.h"

USING_NS_CC;

bool KeyboardController::init() {
    this->m_role = nullptr;

    this->setVelocityX(0);
    this->setVelocityY(0);
    this->scheduleUpdate();

    return true;
}

void KeyboardController::update(float dt) {
    if (this->m_controllerListener == nullptr) {
        return;
    }

    Point pos = this->m_controllerListener->getTagPosition();
    pos.x += this->getVelocityX();
    pos.y += this->getVelocityY();
    this->m_controllerListener->setTagPosition(pos.x, pos.y);
}

void KeyboardController::keyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
    switch(keyCode) {
        // Direction
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            this->m_role->setDirection(true);
            this->m_role->getFSM()->doEvent("walk");
            this->setVelocityX(-3);
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            this->m_role->setDirection(false);
            this->m_role->getFSM()->doEvent("walk");
            this->setVelocityX(3);
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            this->m_role->getFSM()->doEvent("walk");
            this->setVelocityY(3);
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            this->m_role->getFSM()->doEvent("walk");
            this->setVelocityY(-3);
            break;
        // Action
        //case EventKeyboard::KeyCode::KEY_S:
        //    this->m_role->getFSM()->doEvent("attack");
        //    break;
        //case EventKeyboard::KeyCode::KEY_D:
        //    this->m_role->getFSM()->doEvent("skill");
        //    break;
        //default:
        //    break;
    }
}

void KeyboardController::keyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    switch(keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            this->m_role->getFSM()->doEvent("stand");
            this->setVelocityX(0);
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            this->m_role->getFSM()->doEvent("stand");
            this->setVelocityY(0);
            break;
        default:
            break;
    }
}

void KeyboardController::registerWithKeyboardDispatcher() {
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(KeyboardController::keyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(KeyboardController::keyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void KeyboardController::setRole(Role* role) {
    this->m_role = role;
}

Role* KeyboardController::getRole() {
    return this->m_role;
}
