#include "FileLoadUtil.h"
#include "StringUtil.h"

USING_NS_CC;

FileLoadUtil* FileLoadUtil::m_fileLoadUtil = nullptr;

FileLoadUtil* FileLoadUtil::sharedFileLoadUtil() {
    if (m_fileLoadUtil == nullptr) {
        m_fileLoadUtil = new FileLoadUtil();
        
        if (m_fileLoadUtil && m_fileLoadUtil->init()) {
            m_fileLoadUtil->autorelease();
        } else {
            CC_SAFE_DELETE(m_fileLoadUtil);
            m_fileLoadUtil = nullptr;
        }
    }

    return m_fileLoadUtil;
}

bool FileLoadUtil::init() {
    return true;
}

std::vector<std::string> FileLoadUtil::getDataLines(const char* sFilePath) {
    std::vector<std::string> linesList;

    std::string str = FileUtils::getInstance()->getStringFromFile(sFilePath);
    linesList = StringUtil::sharedStrUtil()->split(str.c_str(), "\n");

    return linesList;
}