#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "../../Entity/Role/Player.h"
#include "../../Controller/ContactListener.h"

class GameLayer : public cocos2d::Layer {
public:
	enum EntityType {
		TYPE_WEAPON,
		TYPE_BOUNDED,
		TYPE_ENEMY
	};

    virtual bool init();
    CREATE_FUNC(GameLayer);

    void logic(float dt);

    void initPhysics();
    void updatePhysicsBody(float dt);
    bool collisionDetection(const BoundingBox &bodyBoxA, const BoundingBox &bodyBoxB);
    void updateActionScope(float dt);

    void setListener();

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void onContactSeperate(cocos2d::PhysicsContact& contact);

    cocos2d::Vec2 boundLayerPos(cocos2d::Vec2 newPos);
    void panForTranslation(cocos2d::Vec2 translation);

    void setPhysicsWorld(cocos2d::PhysicsWorld* world);

    cocos2d::Vec2 mapTileCoordToPos(cocos2d::Vec2 coord);

    void addBall(cocos2d::Vec2 position);
    void addEnemyWave();

	void updateDeadBody(float dt);

private:
    cocos2d::TMXTiledMap* m_map;

    cocos2d::EventListenerTouchOneByOne* m_touchListener;

	cocos2d::EventListenerKeyboard* m_keyboardListener;

	cocos2d::EventListenerPhysicsContact* m_contactListener;

    cocos2d::Vec2 m_cursorPos;

    cocos2d::PhysicsWorld* m_world;

    int m_waitTime;

    bool isInterrupted;

	cocos2d::Vector<cocos2d::Node*> destroyEntities;

};

#endif