#include "AnimationManager.h"

static AnimationManager* instance = nullptr;

AnimationManager* AnimationManager::getInstance()
{
	if (!instance)
	{
		instance = new AnimationManager();
	}
	return instance;
}

void AnimationManager::initBattle3Animation()
{
	initUniversalAnimation();
	initBossAnimation();
	initAirBombAnimation();
	initAirEnemyAnimation();
}

void AnimationManager::initUniversalAnimation()
{
	if (AnimationCache::getInstance()->getAnimation("eBombExplode") == nullptr)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemyBomb/eBombExplode.plist");
		Vector<SpriteFrame*>vec;
		for (int i = 0; i < 20; ++i)
		{
			auto fileName = StringUtils::format("image%d.png", 1929 + i * 2);
			vec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
		}
		auto ani = Animation::createWithSpriteFrames(vec);
		ani->setDelayPerUnit(0.1);
		AnimationCache::getInstance()->addAnimation(ani, "eBombExplode");
	}
}

void AnimationManager::initBossAnimation()
{
	if (AnimationCache::getInstance()->getAnimation("bossBombExplode") == nullptr)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BossBomb/explode.plist");
		Vector<SpriteFrame*>vec;
		for (int i = 0; i < 15; ++i)
		{
			auto fileName = StringUtils::format("image%d.png", 20 + i * 2);
			vec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
		}
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vec, 0.1), "bossBombExplode");
	}
	if (AnimationCache::getInstance()->getAnimation("bossBombLaunch") == nullptr)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BossBomb/launch.plist");
		Vector<SpriteFrame*>vec;
		for (int i = 0; i < 4; ++i)
		{
			auto fileName = StringUtils::format("image%d.png", 969 + i * 2);
			vec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
		}
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vec, 0.1), "bossBombLaunch");
	}
	if (AnimationCache::getInstance()->getAnimation("bossBulletExplode") == nullptr)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BossBullet/BossBullet.plist");
		Vector<SpriteFrame*>vec;
		for (int i = 0; i < 6; ++i)
		{
			auto fileName = StringUtils::format("image%d.png", 1275 + i * 2);
			vec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
		}
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vec, 0.1), "bossBulletExplode");
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vec, 0.1), "tinyExplode");
	}
	if (AnimationCache::getInstance()->getAnimation("GearExplode") == nullptr)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Boss/GearExplode.plist");
		Vector<SpriteFrame*>vec;
		for (int i = 0; i < 17; ++i)
		{
			auto fileName = StringUtils::format("image%d.png", 325 + i * 2);
			vec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
		}
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vec, 0.1), "GearExplode");
	}
}

void AnimationManager::initAirBombAnimation()
{
	if (AnimationCache::getInstance()->getAnimation("eBombExplode") == nullptr)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemyBomb/eBombExplode.plist");
		Vector<SpriteFrame*>vec;
		for (int i = 0; i < 20; ++i)
		{
			auto fileName = StringUtils::format("image%d.png", 1929 + i * 2);
			vec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
		}
		auto ani = Animation::createWithSpriteFrames(vec);
		ani->setDelayPerUnit(0.1);
		AnimationCache::getInstance()->addAnimation(ani, "eBombExplode");
	}
}

void AnimationManager::initAirEnemyAnimation()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("airEnemy/EnemyInAir.plist");
	if (AnimationCache::getInstance()->getAnimation("EnemyInAir") == nullptr)
	{
		Vector<SpriteFrame*>vec;
		for (int i = 0; i < 6; ++i)
		{
			auto fileName = StringUtils::format("image%d.png", 3036 + i * 2);
			vec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
		}
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vec, 0.1), "EnemyInAir");
	}
}