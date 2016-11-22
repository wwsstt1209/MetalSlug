#include "EnemyNoGunCommon.h"

EnemyNoGunCommon* EnemyNoGunCommon::create()
{
	EnemyNoGunCommon* ret = new(std::nothrow) EnemyNoGunCommon();
	if (ret&&ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool EnemyNoGunCommon::init()
{
	if (!EnemyNoGun::init())
	{
		return 0;
	}
	scheduleUpdate();

	m_body = Sprite::create("enemy1/image407.png");
	this->addChild(m_body);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy1/zhenchabing.plist");
	vStand.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("image407.png"));
	vStand.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("image409.png"));


	m_body->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(vStand, 0.3))));

	return 1;
}

void EnemyNoGunCommon::update(float dt)
{

}