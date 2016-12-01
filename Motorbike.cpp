#include "Motorbike.h"

Motorbike* Motorbike::create()
{
	Motorbike* ret = new(std::nothrow) Motorbike();
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

bool Motorbike::init()
{
	if (!Node::init())
	{
		return 0;
	}

	m_bike = Sprite::create("image2874.png");
	m_enemy = Sprite::create("image2873.png");
	this->addChild(m_bike);
	this->addChild(m_enemy);
	m_bike->setPosition(Vec2(-2, -8));
	m_bike->setFlippedX(1);
	m_enemy->setPosition(Vec2(2, 8));

	schedule(CC_CALLBACK_1(Motorbike::textureUpdate, this),0.1,"changeTexture");
	scheduleUpdate();

	return 1;
}

void Motorbike::update(float dt)
{
	this->setPositionX(this->getPositionX() + m_speed);
}

void Motorbike::textureUpdate(float dt)
{
	if (m_bike->getResourceName() == "image2874.png")
	{
		m_bike->initWithFile("image2877.png");
		m_bike->setFlippedX(1);
	}
	else if (m_bike->getResourceName() == "image2877.png")
	{
		m_bike->initWithFile("image2874.png");
		m_bike->setFlippedX(1);
	}
	if (m_enemy->getResourceName() == "image2873.png")
	{
		m_enemy->initWithFile("image2876.png");
	}
	else if (m_enemy->getResourceName() == "image2876.png")
	{
		m_enemy->initWithFile("image2873.png");
	}
}

void Motorbike::setSpeed(int speed)
{
	m_speed = speed;
}