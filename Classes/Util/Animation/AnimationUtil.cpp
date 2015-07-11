#include "AnimationUtil.h"

USING_NS_CC;

Animation* AnimationUtil::createAnimWithFrameName(const char* name) {
    SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame *> frameArray;
    int index = 1;
    
    do {
        SpriteFrame* frame = frameCache->getSpriteFrameByName(String::createWithFormat("%s-%d.png", name, index++)->getCString());

        if (frame == NULL) {
            break;
        }

        frameArray.pushBack(frame);
    } while(true);

    Animation* animation = Animation::createWithSpriteFrames(frameArray, 0.3);
    return animation;
}
