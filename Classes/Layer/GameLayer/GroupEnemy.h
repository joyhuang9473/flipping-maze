#ifndef __GROUP_ENEMY_H__
#define __GROUP_ENEMY_H__

#include "cocos2d.h"

class GroupEnemy : public cocos2d::Node {
public:
    virtual bool init();
    GroupEnemy* initGroupEnemy(int type1Total, int type1Hp, int type2Total, int type2Hp);
    CREATE_FUNC(GroupEnemy);
    
private:
    CC_SYNTHESIZE(int, type1Total, Type1Total);
    CC_SYNTHESIZE(int, type2Total, Type2Total);
    CC_SYNTHESIZE(int, type1Hp, Type1Hp);
    CC_SYNTHESIZE(int, type2Hp, Type2Hp);
    CC_SYNTHESIZE(int, enemyTotal, EnemyTotal);
};

#endif
