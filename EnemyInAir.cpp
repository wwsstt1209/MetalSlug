#include "EnemyInAir.h"

EnemyInAir* EnemyInAir::create()
{
	EnemyInAir* ret = new(std::nothrow) EnemyInAir();
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

bool EnemyInAir::init()
{
	if (!Node::init())
	{
		return 0;
	}
	scheduleUpdate();

	GameInfo::getInstance()->vAirEnemy.pushBack(this);
	m_sprite = Sprite::create();
	this->addChild(m_sprite);
	m_sprite->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("EnemyInAir"))));

	return 1;
}

void EnemyInAir::update(float dt)
{
	this->setPositionX(this->getPositionX() - 1);
	if (this->getPositionX() < -100)
	{
		this->removeFromParent();
		GameInfo::getInstance()->vAirEnemy.eraseObject(this);
	}
}