#include "CSVParseUtil.h"
#include "StringUtil.h"
#include "FileLoadUtil.h"

USING_NS_CC;

CSVParseUtil* CSVParseUtil::m_csvParseUtil = nullptr;

CSVParseUtil* CSVParseUtil::sharedCSVParseUtil() {
    if (m_csvParseUtil == nullptr) {
        m_csvParseUtil = new CSVParseUtil();
        
        if (m_csvParseUtil && m_csvParseUtil->init()) {
            m_csvParseUtil->autorelease();
        } else {
            CC_SAFE_DELETE(m_csvParseUtil);
            m_csvParseUtil = nullptr;
        }
    }
    
    return m_csvParseUtil;
}

bool CSVParseUtil::init() {
    return true;
}

void CSVParseUtil::loadFile(const char* sPath) {
    // csvStringList will be two dimensions table
    std::vector<std::vector<std::string>> csvStrTable;

    std::vector<std::string> linesList = FileLoadUtil::sharedFileLoadUtil()->getDataLines(sPath);

    for (int i = 0 ; i < linesList.size() ; i++) {
        if (!linesList.at(i).empty()) {
            std::vector<std::string> tArr = StringUtil::sharedStrUtil()->split(linesList.at(i).c_str(), ",");

            csvStrTable.push_back(tArr);
        }
    }

    this->m_csvDict.insert(std::pair<const char*, std::vector<std::vector<std::string>>>(sPath, csvStrTable));
}

const Size CSVParseUtil::getFileRowColNum(const char* csvFilePath) {
    std::vector<std::vector<std::string>> csvStrTable = this->m_csvDict.at(csvFilePath);

    int rowNum = csvStrTable.size();
    int colNum = csvStrTable.at(0).size();

    Size size = Size(rowNum, colNum);
    return size;
}

std::string CSVParseUtil::get(int row, int col, const char* csvFilePath) {
    std::vector<std::vector<std::string>> csvStrTable = this->m_csvDict.at(csvFilePath);
    std::vector<std::string> rowArr = csvStrTable.at(row);
    std::string colStr = rowArr.at(col);
    
    return colStr;
}
