#ifndef __FILELOAD_UTIL_H__
#define __FILELOAD_UTIL_H__

#include "cocos2d.h"

class FileLoadUtil : public cocos2d::Node {
public:
    static FileLoadUtil* sharedFileLoadUtil();
    bool init();
    std::vector<std::string> getDataLines(const char* sFilePath);

private:
    static FileLoadUtil* m_fileLoadUtil;
};

#endif
