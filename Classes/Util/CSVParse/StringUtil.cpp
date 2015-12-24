#include "StringUtil.h"

USING_NS_CC;

StringUtil* StringUtil::m_stringUtil = nullptr;

StringUtil* StringUtil::sharedStrUtil() {
    if (m_stringUtil == nullptr) {
        m_stringUtil = new StringUtil();

        if (m_stringUtil && m_stringUtil->init()) {
            m_stringUtil->autorelease();
        } else {
            CC_SAFE_DELETE(m_stringUtil);
            m_stringUtil = nullptr;
        }
    }
    return m_stringUtil;
}

bool StringUtil::init() {
    return true;
}

std::vector<std::string> StringUtil::split(const char* srcStr, const char* sSep) {
    std::vector<std::string> stringList;

    int size = strlen(srcStr);

    std::string str = StringUtils::format("%s", srcStr);

    int startIndex = 0;
    int endIndex = 0;

    endIndex = str.find(sSep);

    while (endIndex > 0) {
        std::string splitStr = str.substr(startIndex, endIndex);
        stringList.push_back(splitStr);

        str = str.substr(endIndex+1, size);
        endIndex = str.find(sSep);
    }

    if (str.compare("") != 0) {
        stringList.push_back(str);
    }

    return stringList;
}