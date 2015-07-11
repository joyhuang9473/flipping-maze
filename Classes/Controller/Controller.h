#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "cocos2d.h"
#include "ControllerListener.h"

class Controller : public cocos2d::Node {
public:
    void setControllerListener(ControllerListener* controllerListener);

protected:
    ControllerListener* m_controllerListener;
};

#endif
