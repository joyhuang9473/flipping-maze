#ifndef __GROUP_PATH_H__
#define __GROUP_PATH_H__

#include "cocos2d.h"
#include "GroupEnemy.h"

class GroupPath : public cocos2d::Node {
public:
    virtual bool init();
    GroupPath* initGroupPath(cocos2d::Vector<GroupEnemy*> paths, int waitTime);
    CREATE_FUNC(GroupPath);

private:
    CC_SYNTHESIZE(cocos2d::Vector<GroupEnemy*>, paths, Paths);
    CC_SYNTHESIZE(int, waitTime, WaitTime);
};

#endif
