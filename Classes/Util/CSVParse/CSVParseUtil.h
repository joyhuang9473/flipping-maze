#ifndef __CSVPARSE_UTIL__
#define __CSVPARSE_UTIL__

#include "cocos2d.h"

class CSVParseUtil : public cocos2d::Node {
public:
    static CSVParseUtil* sharedCSVParseUtil();
    bool init();
    void loadFile(const char* sPath);
    void releaseFile(const char* sPath);
    std::string get(int row, int col, const char* csvFilePath);
    const int getInt(int row, int col, const char* csvFilePath);
    const float getFloat(int row, int col, const char* csvFilePath);
    const cocos2d::Size getFileRowColNum(const char* csvFilePath);
    const int findValueInWithLine(const char* chValue, int valueCol, const char* csvFilePath);

private:
    static CSVParseUtil* m_csvParseUtil;
    std::map<const char*, std::vector<std::vector<std::string>>> m_csvDict;
};

#endif