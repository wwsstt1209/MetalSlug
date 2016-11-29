#include "EnemyBomb.h"

EnemyBomb* EnemyBomb::create()
{
	EnemyBomb* ret = new(std::nothrow) EnemyBomb();
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

bool EnemyBomb::init()
{
	if (!Node::init())
	{
		return 0;
	}

	if (AnimationCache::getInstance()->getAnimation("EnemyBomb") == nullptr)
	{
		Vector<SpriteFrame*>vBomb;
		for (int i = 0; i < 4; ++i)
		{
			auto filename = StringUtils::format("image%d.png", 711 + i * 2);
			auto sf = SpriteFrame::create(filename, Rect(0, 0, 29, 44));
			vBomb.pushBack(sf);
		}
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vBomb, 0.2), "EnemyBomb");
	}

	return 1;
}

void EnemyBomb::initWithUmbrella()
{

	m_bomb = Sprite::create("image711.png");
	this->addChild(m_bomb);
	m_bomb->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("EnemyBomb"))));

	auto umbrella = Sprite::create("airEnemy/image2881.png");
	this->addChild(umbrella);
	umbrella->setPosition(Vec2(0, 50));

	schedule(CC_CALLBACK_1(EnemyBomb::update1, this), 1.0f / 60, "bombWithUmbrella");
}

void EnemyBomb::initBreakTruck()
{
	m_bomb = Sprite::create("image711.png");
	this->addChild(m_bomb);
	m_bomb->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("EnemyBomb"))));

	schedule(CC_CALLBACK_1(EnemyBomb::update2, this), 1.0f / 60, "bombBreakTruck");
}

void EnemyBomb::update1(float dt)
{
	this->setPositionY(this->getPositionY() - 0.5);
}

void EnemyBomb::update2(float dt)
{
	this->setPositionY(this->getPositionY() - 5);
}