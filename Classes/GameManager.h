#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"

class GameManager {
public:
    GameManager();
    ~GameManager();

    static GameManager* getInstance();

    void readStageInfo(const std::string plistpath);
    void clear();

    CC_SYNTHESIZE(std::string, curMapName, CurMapName);
    CC_SYNTHESIZE(std::string, curStageFile, CurStageFile);
    CC_SYNTHESIZE(std::string, nextStageFile, NextStageFile);
    CC_SYNTHESIZE(std::string, curBgName, CurBgName);

private:
    static GameManager* instance;

    cocos2d::ValueMap resources;
    cocos2d::ValueMap stageInfo;
};

#endif
