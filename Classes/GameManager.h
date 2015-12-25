#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"
#include "Layer/GameLayer/GroupPath.h"

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

    CC_SYNTHESIZE(cocos2d::Vector<GroupPath*>, waveVector, WaveVector);

    CC_SYNTHESIZE(int, currWaitTime, CurrWaitTime);
    CC_SYNTHESIZE(int, enemyWaveCounter, EnemyWaveCounter);
    CC_SYNTHESIZE(int, numsOfEnemy, NumsOfEnemy);
    CC_SYNTHESIZE(int, playerLife, PlayerLife);

    bool isFinishedAddWaves();
    bool isMissionComplete();
    bool isMissionFailed();

private:
    static GameManager* instance;

    cocos2d::ValueMap resources;
    cocos2d::ValueMap stageInfo;
};

#endif
