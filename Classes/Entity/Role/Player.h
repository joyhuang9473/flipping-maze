#ifndef __HERO_ENTITY_H__
#define __HERO_ENTITY_H__

#include "cocos2d.h"
#include "Role.h"

class Player : public Role {
public:

	Player();
	~Player();

	virtual bool init();
	CREATE_FUNC(Player);

    void setViewPointByPlayer();
    void setTiledMap(cocos2d::TMXTiledMap* map);

    virtual void setTagPosition(int x, int y);

private:
    cocos2d::TMXTiledMap* m_map;
};

#endif