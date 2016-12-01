#include "EnemyPlane1.h"

EnemyPlane1* EnemyPlane1::create()
{
	EnemyPlane1* ret = new(std::nothrow) EnemyPlane1();
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

bool EnemyPlane1::init()
{
	if (!Node::init())
	{
		return 0;
	}

	m_screw = 1;

	//image706.png
	m_plane = Sprite::create("image706.png");
	this->addChild(m_plane);
	m_airscrew = Sprite::create("image705.png");
	this->addChild(m_airscrew);

	schedule(CC_CALLBACK_1(EnemyPlane1::flyUpdate, this), 0.02, "fly");
	schedule(CC_CALLBACK_1(EnemyPlane1::shootUpdate, this), 5, "shoot");

	return 1;
}

void EnemyPlane1::flyUpdate(float dt)
{
	if (m_screw)
	{
		m_airscrew->setFlippedX(0);
		m_airscrew->setPosition(Vec2(-62, m_plane->getContentSize().height / 2));
		m_screw = 0;
	}
	else
	{
		m_airscrew->setFlippedX(1);
		m_airscrew->setPosition(Vec2(23, m_plane->getContentSize().height / 2));
		m_screw = 1;
	}
}

void EnemyPlane1::shootUpdate(float dt)
{
	auto b = Bullet::create();
	b->initEnemyPlaneBullet1(18);
	b->setPosition(this->getPosition());
	GameInfo::getInstance()->battleScene->addChild(b, 3);
	GameInfo::getInstance()->vEnemyBullet.pushBack(b);
}