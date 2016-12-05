#include "Cannon.h"

Cannon* Cannon::create()
{
	Cannon * ret = new (std::nothrow) Cannon();
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

bool Cannon::init()
{
	if (!Node::init())
	{
		return 0;
	}
	scheduleUpdate();

	spr0 = Sprite::create("onCanon/image2012.png");
	spr0->setPosition(Vec2::ZERO);
	this->addChild(spr0);
	spr1 = Sprite::create("onCanon/image2014.png");
	spr1->setPosition(Vec2(0, 40));
	this->addChild(spr1);

	return 1;
}

void Cannon::updateCannon(bool left)
{
	if (left)
	{
		--m_toward;
		if (m_toward < -8)
			m_toward = -8;
	}
	else
	{
		++m_toward;
		if (m_toward > 8)
			m_toward = 8;
	}
	if (m_toward < 0)
		this->setScaleX(-1);
	else
		this->setScaleX(1);
	auto fileName = StringUtils::format("onCanon/image%d.png", 2014 + (int)(sqrt(m_toward*m_toward)) * 2);
	spr1->initWithFile(fileName);
}

void Cannon::resetCannon()
{
	fire(0);
	m_toward = 0;
	spr1->initWithFile("onCanon/image2014.png");
}

void Cannon::fire(bool b)
{
	if (!m_fire && b)
	{
		m_fire = b;
		schedule(CC_CALLBACK_0(Cannon::fireUpdate, this), 0.2, "Fire");
	}
	else if (m_fire && !b)
	{
		m_fire = b;
		unschedule("Fire");
	}
	else
	{
		return;
	}
}

void Cannon::fireUpdate()
{
	auto b = Bullet::create();
	b->initCannonBullet(m_toward);
}