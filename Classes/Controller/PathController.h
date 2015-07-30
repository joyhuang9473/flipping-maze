#ifndef __PATH_CONTROLLER_H__
#define __PATH_CONTROLLER_H__

#include "cocos2d.h"
#include "Controller.h"
#include "../Entity/Role/Role.h"

class PathController : public Controller {
public:
    enum AIState {
        AI_REACH,
        AI_IDLE,
        AI_PATROL,
        AI_PURSUIT
    };

	CREATE_FUNC(PathController);
    virtual bool init();
    virtual void update(float dt);
    void updateExecute(float dt);

    void decide();

	void setRole(Role* role);
	Role* getRole();

    cocos2d::Vec2 getCurrentPathPoint();
    void nextPathPoint();

private:
	Role* m_role;

    CC_SYNTHESIZE(int, m_VelocityX, VelocityX);
    CC_SYNTHESIZE(int, m_VelocityY, VelocityY);

	CC_SYNTHESIZE(std::vector<cocos2d::Vec2>, m_pathPoints, PathPoints);
    int m_pointCounter;

    CC_SYNTHESIZE(cocos2d::Vec2, m_moveDirection, MoveDirection);
    CC_SYNTHESIZE(float, m_eyeArea, EyeArea);
    CC_SYNTHESIZE(AIState, m_aiState, AIState);
    unsigned int m_nextDecisionTime;
};

#endif
