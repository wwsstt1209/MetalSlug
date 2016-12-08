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
			auto filename = StringUtils::format("enemyBomb/image%d.png", 711 + i * 2);
			auto sf = SpriteFrame::create(filename, Rect(0, 0, 29, 44));
			vBomb.pushBack(sf);
		}
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vBomb, 0.2), "EnemyBomb");
	}

	GameInfo::getInstance()->vEnemyBomb.pushBack(this);

	return 1;
}

void EnemyBomb::initWithUmbrella()
{
	m_bomb = Sprite::create("enemyBomb/image711.png");
	this->addChild(m_bomb);
	m_bomb->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("EnemyBomb"))));

	m_umbrella = Sprite::create("airEnemy/image2881.png");
	this->addChild(m_umbrella);
	m_umbrella->setPosition(Vec2(0, 50));

	scheduleUpdate();
	schedule(CC_CALLBACK_1(EnemyBomb::update1, this), 1.0f / 60, "bombWithUmbrella");
}

void EnemyBomb::initBreakTruck()
{
	m_bomb = Sprite::create("enemyBomb/image711.png");
	this->addChild(m_bomb);
	m_bomb->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("EnemyBomb"))));

	scheduleUpdate();
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

void EnemyBomb::update(float dt)	
{
	auto hero = GameInfo::getInstance()->m_hero;
	auto posHeroInBomb = this->convertToNodeSpace(hero->getPosition());
	if (fabs(m_bomb->getPositionX() - posHeroInBomb.x) <= 25 && fabs(m_bomb->getPositionY() - posHeroInBomb.y) <= 75)
	{
		m_bomb->stopAllActions();
		m_bomb->setRotation(0);
		if (m_umbrella)
			m_umbrella->setVisible(0);
		auto release = CallFunc::create([this]()->void{
			GameInfo::getInstance()->vEnemyBomb.eraseObject(this);
			this->removeFromParent();
		});
		m_bomb->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("eBombExplode")), release, nullptr));
		unscheduleUpdate();
		unschedule("bombWithUmbrella");
		unschedule("bombBreakTruck");
	}
	if (this->getPositionY() <= -100)
	{
		GameInfo::getInstance()->vEnemyBomb.eraseObject(this);
		this->removeFromParent();
	}
}