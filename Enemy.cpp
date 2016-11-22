#include "Enemy.h"

Enemy* Enemy::create()
{
	Enemy * ret = new (std::nothrow) Enemy();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool Enemy::init()
{
	if (!Node::init())
	{
		return 0;
	}

	this->loadDeadSource();

	return 1;
}

void Enemy::loadDeadSource()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy1/EnemyDead.png");
	for (int i = 0; i < 11; ++i)
	{
		auto fileName = StringUtils::format("image%d.png", 620 + i * 2);
		vDead1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fileName"));
	}
	AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vDead1, 0.1),"dead1");

	for (int i = 0; i < 10; ++i)
	{
		auto fileName = StringUtils::format("image%d.png", 658 + i * 2);
		vDead2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fileName"));
	}
	AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vDead2, 0.1), "dead2");

	for (int i = 0; i < 7; ++i)
	{
		auto fileName = StringUtils::format("image%d.png", 643 + i * 2);
		vDead3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fileName"));
	}
	AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vDead3, 0.1), "dead3");
}