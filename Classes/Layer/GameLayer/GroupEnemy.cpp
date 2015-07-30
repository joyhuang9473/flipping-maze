#include "GroupEnemy.h"

bool GroupEnemy::init() {
    return true;
}

GroupEnemy* GroupEnemy::initGroupEnemy(int type1Total, int type1Hp, int type2Total, int type2Hp) {
    this->type1Total = type1Total;
    this->type2Total = type2Total;
    this->type1Hp = type1Hp;
    this->type2Hp = type2Hp;
    this->enemyTotal = type1Total + type2Total;
    return this;
}
