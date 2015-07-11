#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__

#include "cocos2d.h"

class StringUtil : public cocos2d::Node {
public:
    static StringUtil* sharedStrUtil();
    bool init();
    std::vector<std::string> split(const char* srcStr, const char* sSep);

private:
    static StringUtil* m_stringUtil;
};

#endif
