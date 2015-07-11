#ifndef __PROGRESS_h__
#define __PROGRESS_h__

#include "cocos2d.h"

class Progress : public cocos2d::Sprite {
public:
    Progress();
    ~Progress();

    virtual bool init();
    CREATE_FUNC(Progress);

    static Progress* create(const char* background, const char* fillname);

    void setFill(cocos2d::ProgressTimer* fill);

    void setProgress(float percentage);

private:
    cocos2d::ProgressTimer* m_fill;
};

#endif