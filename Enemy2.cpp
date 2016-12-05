#include "Enemy2.h"

Enemy2* Enemy2::create()
{
	Enemy2* ret = new(std::nothrow) Enemy2();
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

bool Enemy2::init()
{
	if (!Node::init())
	{
		return 0;
	}
	scheduleUpdate();
	schedule(CC_CALLBACK_0(Enemy2::shoot, this), 3, "enemy2shoot");

	m_sprite = Sprite::create();
	this->addChild(m_sprite);
	m_sprite->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("enemyStand"))));

	GameInfo::getInstance()->vEnemy.pushBack(this);

	return 1;
}

void Enemy2::shoot()
{
	auto hero = GameInfo::getInstance()->m_hero;
	auto posHeroInEnemy = this->convertToNodeSpaceAR(hero->getPosition());
	auto posInWorld = this->convertToWorldSpace(Vec2::ZERO);
	auto posInScene = GameInfo::getInstance()->battleScene->convertToNodeSpace(posInWorld);
	if (fabs(posHeroInEnemy.x) <= 250)
	{
		auto b = Bullet::create();
		b->setScaleY(0.2);
		if (posHeroInEnemy.x < 0)
		{
			m_sprite->setFlippedX(0);
			b->initEnemy2Bullet(-5);
			b->setPosition(Vec2(-20, 10) + posInScene);
		}
		else
		{
			m_sprite->setFlippedX(1);
			b->initEnemy2Bullet(5);
			b->setPosition(Vec2(20, 10) + posInScene);
		}
		auto setStand = CallFunc::create([this]()->void{
			m_sprite->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("enemyStand"))));
		});
		m_sprite->stopAllActions();
		m_sprite->runAction(Sequence::create(
			Animate::create(AnimationCache::getInstance()->getAnimation("enemyStandShoot")),
			setStand, nullptr));
	}
}

void Enemy2::update(float dt)
{
	auto posInWorld = this->convertToWorldSpace(Vec2::ZERO);
	auto posInScene = GameInfo::getInstance()->battleScene->convertToNodeSpace(posInWorld);
	if (posInScene.x < -50)
	{
		GameInfo::getInstance()->vEnemy.eraseObject(this);
		this->removeFromParent();
	}
}