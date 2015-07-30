#ifndef __ENEMY_ENTITY_H__
#define __ENEMY_ENTITY_H__

#include "cocos2d.h"
#include "Role.h"

class Enemy : public Role {
public:

	Enemy();
	~Enemy();

	virtual bool init();
	CREATE_FUNC(Enemy);

    virtual void setTagPosition(int x, int y);

	void setWithPhysics();
};

#endif