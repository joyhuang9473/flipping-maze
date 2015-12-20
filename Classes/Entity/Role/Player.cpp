#include "Player.h"
#include "../../Util/Animation/AnimationUtil.h"

USING_NS_CC;

#define FRAMECACHE SpriteFrameCache::getInstance()

Player::Player() {}

Player::~Player() {
    CC_SAFE_RELEASE(m_map);
}

bool Player::init() {
	this->m_map = nullptr;

	/*
	** It should be adjsuted
	*/
	// Sprite Frame
	FRAMECACHE->addSpriteFramesWithFile("hero-kisi.plist", "hero-kisi.png");
    std::string spName = "kisi";
    Sprite* heroSprite = Sprite::createWithSpriteFrame(FRAMECACHE->getSpriteFrameByName(StringUtils::format("%s-idle-1.png", spName.c_str())));
    this->bindSprite(heroSprite);

	/*
	** It should be adjsuted
	*/
    // Animation
    Animation* standAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-idle", spName.c_str()).c_str());
    Animation* moveAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-move", spName.c_str()).c_str());
    //Animation* attackAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-attack", spName.c_str()).c_str());
    //Animation* skillAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-skill", spName.c_str()).c_str());
    //Animation* injuredAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-hurt", spName.c_str()).c_str());
    //Animation* dieAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-die", spName.c_str()).c_str());
    
    this->setStandAction(standAnim);
    this->setMoveAction(moveAnim);
    //this->setAttackAction(attackAnim);
    //this->setSkillAction(skillAnim);
    //this->setInjuredAction(injuredAnim);
    //this->setDieAction(dieAnim);
    
    return true;
}

void Player::setViewPointByPlayer() {
    if (this->getSprite() == nullptr) {
        return;
    }

    Layer* parent = (Layer*)this->getParent();

    Size mapTiledNum = this->m_map->getMapSize();
    Size tiledSize = this->m_map->getTileSize();
    Size mapSize = Size(mapTiledNum.width*tiledSize.width,
                        mapTiledNum.height*tiledSize.height);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point spritePos = this->getPosition();

    float x = fmax(spritePos.x, visibleSize.width/2);
    float y = fmax(spritePos.y, visibleSize.height/2);

    x = fmin(x, mapSize.width - visibleSize.width/2);
    y = fmin(y, mapSize.height - visibleSize.height/2);
    
    Point destPos = Vec2(x, y);
    Point centerPos = Vec2(visibleSize.width/2, visibleSize.height/2);
    Point viewPos = centerPos - destPos;

    parent->setPosition(viewPos);
}

void Player::setTagPosition(int x, int y) {
    Role::setTagPosition(x, y);
    this->setViewPointByPlayer();
}

