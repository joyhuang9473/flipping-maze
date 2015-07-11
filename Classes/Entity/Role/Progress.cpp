#include "Progress.h"

USING_NS_CC;

Progress::Progress() {
    std::vector<std::string> searchPaths;
    searchPaths.push_back("Other");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
}

Progress::~Progress() {}

bool Progress::init() {
    this->initWithFile("progress-bg.png");
    ProgressTimer* fill = ProgressTimer::create(Sprite::create("progress-fill.png"));
    this->setFill(fill);
    this->addChild(fill);

    fill->setType(ProgressTimer::Type::BAR);
    fill->setMidpoint(Point(0, 0.5));
    fill->setBarChangeRate(Point(1.0, 0));
    fill->setPosition(this->getContentSize()/2);
    fill->setPercentage(100);
    return true;
}

void Progress::setFill(ProgressTimer *fill) {
    this->m_fill = fill;
}

void Progress::setProgress(float percentage) {
    this->m_fill->setPercentage(percentage);
}
