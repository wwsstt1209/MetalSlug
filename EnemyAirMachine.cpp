#include "EnemyAirMachine.h"

EnemyAirMachine* EnemyAirMachine::create()
{
	EnemyAirMachine* ret = new(std::nothrow) EnemyAirMachine();
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

bool EnemyAirMachine::init()
{
	if (!Node::init())
	{
		return 0;
	}

	GameInfo::getInstance()->vAirEnemy.pushBack(this);
	m_sprite = Sprite::create();
	this->addChild(m_sprite);

	return 1;
}

void EnemyAirMachine::update(float dt)
{
	if (this->getPositionX() < -100)
	{
		GameInfo::getInstance()->vAirEnemy.eraseObject(this);
		this->removeFromParent();
	}
}