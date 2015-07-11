#include "VisibleRect.h"

USING_NS_CC;

#define VISIBLERECT Director::getInstance()->getOpenGLView()->getVisibleRect()

Rect VisibleRect::s_visibleRect;

void VisibleRect::init() {
    s_visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
}

Rect VisibleRect::getVisibleRect() {
    return VISIBLERECT;
}

Point VisibleRect::left() {
    return Point(VISIBLERECT.origin.x, VISIBLERECT.origin.y + VISIBLERECT.size.height/2);
}

Point VisibleRect::right() {
    return Point(VISIBLERECT.origin.x + VISIBLERECT.size.width, VISIBLERECT.origin.y + VISIBLERECT.size.height/2);
}

Point VisibleRect::top() {
    return Point(VISIBLERECT.origin.x + VISIBLERECT.size.width/2, VISIBLERECT.origin.y + VISIBLERECT.size.height);
}

Point VisibleRect::bottom() {
    return Point(VISIBLERECT.origin.x + VISIBLERECT.size.width/2, VISIBLERECT.origin.y);
}

Point VisibleRect::center() {
    return Point(VISIBLERECT.origin.x + VISIBLERECT.size.width/2, VISIBLERECT.origin.y + VISIBLERECT.size.height/2);
}

Point VisibleRect::leftTop() {
    return Point(VISIBLERECT.origin.x, VISIBLERECT.origin.y + VISIBLERECT.size.height);
}

Point VisibleRect::rightTop() {
    return Point(VISIBLERECT.origin.x + VISIBLERECT.size.width, VISIBLERECT.origin.y + VISIBLERECT.size.height);
}

Point VisibleRect::leftBottom() {
    return VISIBLERECT.origin;
}

Point VisibleRect::rightBottom() {
    return Point(VISIBLERECT.origin.x + VISIBLERECT.size.width, VISIBLERECT.origin.y);
}
