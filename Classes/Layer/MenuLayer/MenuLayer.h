#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__
#include "cocos2d.h"

class MenuLayer : public cocos2d::Layer {
public:
    virtual bool init();

    CREATE_FUNC(MenuLayer);

    void menuStartCallback();

    void menuCloseCallback(cocos2d::Ref* pSender);

    void setBackground();

    virtual void update(float dt);

};

#endif