#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::Scene {
public:
    virtual bool init();

    CREATE_FUNC(GameScene);

    static cocos2d::Scene* createWithPhysicsWorld();

    void createCompleteDialog();

    void createFailedDialog();

    void menuCallback();
};

#endif