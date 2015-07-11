#ifndef __CONTROLLER_LISTENER_H__
#define __CONTROLLER_LISTENER_H__

#include "cocos2d.h"

class ControllerListener {
public:
    virtual void setTagPosition(int x, int y) = 0;
    virtual cocos2d::Point getTagPosition() = 0;
};

#endif
