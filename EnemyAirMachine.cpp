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
	m_sprite = Sprite::create("image3065.png");
	this->addChild(m_sprite);
	this->runAction(MoveBy::create(2, Vec2(-150, 0)));
	m_time = 0;

	scheduleUpdate();

	return 1;
}

void EnemyAirMachine::update(float dt)
{
	m_time += dt;
	if (m_time >= 2)
	{
		m_time -= 2;
		shoot();
	}

	if (m_upToDown)
	{
		this->setPositionY(this->getPositionY() - 1);
	}
	else
	{
		this->setPositionY(this->getPositionY() + 1);
	}

	if (this->getPositionY() >= 350)
	{
		m_upToDown = 1;
	}
	else if (this->getPositionY() <= 50)
	{
		m_upToDown = 0;
	}

	if (this->getPositionX() < -100)
	{
		GameInfo::getInstance()->vAirEnemy.eraseObject(this);
		this->removeFromParent();
	}
}

void EnemyAirMachine::shoot()
{
	auto b = Bullet::create();
	b->setPosition(this->getPosition() + Vec2(-70, 20));
	b->initEnemyBullet(10);
}