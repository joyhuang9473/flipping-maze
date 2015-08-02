#include "Enemy.h"
#include "../../Util/Animation/AnimationUtil.h"

USING_NS_CC;

#define FRAMECACHE SpriteFrameCache::getInstance()

Enemy::Enemy() {}

Enemy::~Enemy() {
    CC_SAFE_RELEASE(m_map);
}

bool Enemy::init() {
	this->m_map = nullptr;

	// Sprite Frame
	FRAMECACHE->addSpriteFramesWithFile("hero-kisi.plist", "hero-kisi.png");
    std::string spName = "kisi";
    Sprite* heroSprite = Sprite::createWithSpriteFrame(FRAMECACHE->getSpriteFrameByName(StringUtils::format("%s-idle-1.png", spName.c_str())));
    this->bindSprite(heroSprite);

    // Animation
    Animation* standAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-idle", spName.c_str()).c_str());
    Animation* moveAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-move", spName.c_str()).c_str());
	Animation* injuredAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-hurt", spName.c_str()).c_str());
	Animation* dieAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-die", spName.c_str()).c_str());

	// Basic attribute
	this->setHp(1);
	this->setMaxHp(1);

    this->setStandAction(standAnim);
    this->setMoveAction(moveAnim);
	this->setInjuredAction(injuredAnim);
	this->setDieAction(dieAnim);

    return true;
}

void Enemy::setTagPosition(int x, int y) {
    Role::setTagPosition(x, y);
}

void Enemy::setWithPhysics() {
	auto boundBody = PhysicsBody::createBox(this->getSprite()->getContentSize() / 2, PhysicsMaterial(1.0f, 1.0f, 0.0f));
	boundBody->setGravityEnable(false);
	this->setPhysicsBody(boundBody);
}