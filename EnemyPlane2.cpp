#include "EnemyPlane2.h"

EnemyPlane2* EnemyPlane2::create()
{
	EnemyPlane2* ret = new(std::nothrow) EnemyPlane2();
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

bool EnemyPlane2::init()
{
	if (!Node::init())
	{
		return 0;
	}

	m_screw = 1;
	m_moveToRight = 1;

	//image706.png
	m_plane = Sprite::create("image2866.png");
	this->addChild(m_plane);
	m_airscrew = Sprite::create("image2868.png");
	m_airscrew->setPosition(Vec2(0, 10));
	this->addChild(m_airscrew);

	schedule(CC_CALLBACK_1(EnemyPlane2::flyUpdate, this), 0.02, "fly");
	schedule(CC_CALLBACK_1(EnemyPlane2::shootUpdate, this), 3, "shoot");
	scheduleUpdate();

	GameInfo::getInstance()->vEnemy.pushBack(this);

	return 1;
}

void EnemyPlane2::update(float dt)
{
	if (m_moveToRight)
	{
		this->setPositionX(this->getPositionX() + 2);
	}
	else
	{
		this->setPositionX(this->getPositionX() - 2);
	}
	if (this->getPositionX() > Director::getInstance()->getVisibleSize().width - 50)
	{
		m_moveToRight = 0;
	}
	else if (this->getPositionX() < 50)
	{
		m_moveToRight = 1;
	}
}

void EnemyPlane2::flyUpdate(float dt)
{
	if (m_screw)
	{
		m_screw = 0;
		m_airscrew->initWithFile("image2865.png");
		m_airscrew->setPosition(Vec2(0, 30));
	}
	else
	{
		m_screw = 1;
		m_airscrew->initWithFile("image2868.png");
		m_airscrew->setPosition(Vec2(0, 10));
	}
}

void EnemyPlane2::shootUpdate(float dt)
{
	auto shootCallback = CallFunc::create([this]()->void{
		auto b = Bullet::create();
		b->initEnemyPlaneBullet2(3);
		b->setPosition(Vec2(0, -85) + this->getPosition());
	});
	this->runAction(Sequence::create(shootCallback, DelayTime::create(0.3), shootCallback, DelayTime::create(0.3), shootCallback,nullptr));
}