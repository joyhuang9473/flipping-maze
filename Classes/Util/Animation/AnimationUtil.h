#ifndef __ANIMATION_UTIL_H__
#define __ANIMATION_UTIL_H__

#include "cocos2d.h"

class AnimationUtil {
public:
    static cocos2d::Animation* createAnimWithFrameName(const char* name);
};

#endif