#include "TinyEnemyPlane.h"

TineEnemyPlane* TineEnemyPlane::create()
{
	TineEnemyPlane* ret = new(std::nothrow) TineEnemyPlane();
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

bool TineEnemyPlane::init()
{
	if (!Node::init())
	{
		return 0;
	}
	scheduleUpdate();

	GameInfo::getInstance()->vAirEnemy.pushBack(this);

	m_sprite = Sprite::create("image2977.png");
	this->addChild(m_sprite);

	m_speedMax = -10;


	return 1;
}


void TineEnemyPlane::update(float dt)
{
	this->setPositionX(this->getPositionX() + m_speedMax);
	m_speedMax += 0.09;

	if (this->getPositionX() < 50)
	{
		m_sprite->stopAllActions();
		m_sprite->initWithFile("image2999.png");
	}
	else if (this->getPositionX() >= 50 && this->getPositionX() < 150)
	{
		m_sprite->stopAllActions();
		m_sprite->initWithFile("image2997.png");
	}
	else
	{
		m_sprite->initWithFile("image2977.png");
	}
	//if (this->getPositionX() >= 80 && this->getPositionX() < 200)
	//	m_sprite->initWithFile("image2995.png");
	//if (this->getPositionX() >= 200 && this->getPositionX() < 380)
	//	m_sprite->initWithFile("image2993.png");
	//if (this->getPositionX() >= 380 && this->getPositionX() < 560)
	//	m_sprite->initWithFile("image2991.png");

	if (m_speedMax > 0)
		m_sprite->setFlippedX(1);
	if (m_speedMax > 0 && this->getPositionX() > 560)
	{
		GameInfo::getInstance()->vAirEnemy.eraseObject(this);
		this->removeFromParent();
	}
}