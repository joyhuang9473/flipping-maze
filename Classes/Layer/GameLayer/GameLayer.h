#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "../../Entity/Role/Player.h"
#include "../../Controller/ContactListener.h"

class GameLayer : public cocos2d::Layer {
public:

    virtual bool init();
    CREATE_FUNC(GameLayer);
    void setPlayer(cocos2d::TMXTiledMap* map, Player* player);

    bool collisionDetection(const BoundingBox &hitBox, const BoundingBox &bodyBox);

    void initPhysics();
    void addBoxBodyForRole(Role* role);
    void updateBoxBody(float dt);

    void logic(float dt);
    void updateActionScope(float dt);

private:
    Player* m_player;
    b2World* m_world;
    ContactListener* m_contactListener;

    cocos2d::TMXTiledMap* m_map;

    bool isMissionComplete;
    bool isInterrupted;
};

#endif