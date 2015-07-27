#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "../../Entity/Role/Player.h"
#include "../../Controller/ContactListener.h"

class GameLayer : public cocos2d::Layer {
public:

    virtual bool init();
    CREATE_FUNC(GameLayer);
    //void setPlayer(Player* player);
	//void bindRoleToMap(Role* role, cocos2d::TMXTiledMap* map);

	void logic(float dt);
    
    void initPhysics();
    void setPhysicsBodyForRole(Role* role);
    void updatePhysicsBody(float dt);
	bool collisionDetection(const BoundingBox &bodyBoxA, const BoundingBox &bodyBoxB);
	void updateActionScope(float dt);

	void setListener();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	cocos2d::Vec2 boundLayerPos(cocos2d::Vec2 newPos);
	void panForTranslation(cocos2d::Vec2 translation);

private:
    cocos2d::TMXTiledMap* m_map;

	cocos2d::EventListenerTouchOneByOne* m_touchListener;

	cocos2d::Vec2 m_cursorPos;
};

#endif