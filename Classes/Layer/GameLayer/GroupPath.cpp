#include "GroupPath.h"

USING_NS_CC;

bool GroupPath::init() {
    return true;
}

GroupPath* GroupPath::initGroupPath(Vector<GroupEnemy*> wavePaths, int waitTime) {
    this->paths = wavePaths;
    this->waitTime = waitTime;
    return this;
}
