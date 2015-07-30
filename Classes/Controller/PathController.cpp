#include "PathController.h"

USING_NS_CC;

bool PathController::init() {
    this->m_role = nullptr;

	this->m_pointCounter = 0;

    this->m_eyeArea = 380;
    this->m_moveDirection.x = 0;
    this->m_moveDirection.y = 0;

    this->m_nextDecisionTime = 0;

    this->setVelocityX(0);
    this->setVelocityY(0);

    this->scheduleUpdate();
	this->schedule(schedule_selector(PathController::updateExecute));

    return true;
}

void PathController::update(float dt) {
    if (this->m_controllerListener == nullptr) {
        return;
    }

    Point pos = this->m_controllerListener->getTagPosition();
    pos.x += this->getVelocityX();
    pos.y += this->getVelocityY();
    this->m_controllerListener->setTagPosition(pos.x, pos.y);
}

void PathController::updateExecute(float dt) {
    if (this->m_role == nullptr) {
        return;
    }

    if (this->m_nextDecisionTime <= 0) {
        this->decide();
    } else {
        --this->m_nextDecisionTime;
    }
}

void PathController::setRole(Role* role) {
    this->m_role = role;
}

Role* PathController::getRole() {
    return this->m_role;
}

Vec2 PathController::getCurrentPathPoint() {
	return this->m_pathPoints.at(this->m_pointCounter);
}

void PathController::nextPathPoint() {
	int lastPathPoint = (int)this->m_pathPoints.size() - 1;

	if (this->m_pointCounter < lastPathPoint) {
		++this->m_pointCounter;
    }
}

void PathController::decide() {
    Vec2 location = this->m_controllerListener->getTagPosition();
    Vec2 target = this->getCurrentPathPoint();
    float distance = location.getDistance(target);
    bool isFlippedX = this->m_role->getSprite()->isFlippedX();
    bool isOnTargetLeft = (location.x < target.x) ? true : false;

    if (
         (isFlippedX && isOnTargetLeft)
      || (!isFlippedX && !isOnTargetLeft)
    ) {
        this->m_aiState = (CCRANDOM_0_1() > 0.5f) ? AI_PATROL : AI_IDLE;
    } else {
       if (distance < this->m_eyeArea) {
           this->m_aiState = (fabsf(location.y - target.y) < 5) ? AI_REACH : AI_PURSUIT;
       } else {
		 this->m_aiState = (CCRANDOM_0_1() > 0.5f) ? AI_PURSUIT : AI_PATROL;
       }
    }

    switch (this->m_aiState) {
        case AIState::AI_REACH:
        {
            this->nextPathPoint();

            this->setVelocityX(0);
            this->setVelocityY(0);
            this->m_role->getFSM()->doEvent("stand");
            this->m_nextDecisionTime = 15;
            break;
        }
        case AIState::AI_IDLE:
        {
            this->setVelocityX(0);
            this->setVelocityY(0);
            this->m_role->getFSM()->doEvent("stand");
            this->m_nextDecisionTime = 15;
            break;
        }
        case AIState::AI_PATROL:
        {
            this->m_role->getFSM()->doEvent("walk");
            this->m_moveDirection.x = CCRANDOM_MINUS1_1();
            this->m_moveDirection.y = CCRANDOM_MINUS1_1();
            this->m_role->setDirection((this->m_moveDirection.x < 0) ? true : false);

            this->setVelocityX((this->m_moveDirection.x < 0) ? -1 : 1);
            this->setVelocityY((this->m_moveDirection.y < 0) ? -1 : 1);
            this->m_nextDecisionTime = 10;
            break;
        }
        case AIState::AI_PURSUIT:
        {
            this->m_role->getFSM()->doEvent("walk");
            this->m_moveDirection = (target - location).getNormalized();
            this->m_role->setDirection((this->m_moveDirection.x < 0) ? true : false);

            this->setVelocityX((this->m_moveDirection.x < 0) ? -1 : 1);
            this->setVelocityY((this->m_moveDirection.y < 0) ? -1 : 1);
            this->m_nextDecisionTime = 10;
            break;
        }
        default:
            this->m_role->getFSM()->doEvent("stand");
            break;
    }
}

