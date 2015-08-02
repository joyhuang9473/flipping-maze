#ifndef __KEYBOARD_CONTROLLER_H__
#define __KEYBOARD_CONTROLLER_H__

#include "cocos2d.h"
#include "Controller.h"
#include "../Entity/Role/Role.h"

class KeyboardController : public Controller {
public:
	CREATE_FUNC(KeyboardController);
    virtual bool init();
    virtual void update(float dt);

    virtual void registerWithKeyboardDispatcher();
    virtual void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    virtual void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	void setRole(Role* role);
	Role* getRole();

private:
	Role* m_role;
    CC_SYNTHESIZE(int, m_VelocityX, VelocityX);
    CC_SYNTHESIZE(int, m_VelocityY, VelocityY);
};

#endif
