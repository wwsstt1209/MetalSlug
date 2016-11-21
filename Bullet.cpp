#include "Bullet.h"

Bullet* Bullet::create()
{
	Bullet * ret = new (std::nothrow) Bullet();
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

bool Bullet::init()
{
	if (!Node::create())
	{
		return 0;
	}
	scheduleUpdate();
	m_bulletSprite = Sprite::create();
	m_bulletSprite->setPosition(Vec2::ZERO);
	this->addChild(m_bulletSprite);

	return 1;
}

void Bullet::update(float dt)
{
	switch (m_toward)
	{
	case 0:
		this->setRotation(-90);
		this->setPositionY(this->getPositionY() + m_speed);
		break;
	case 1:
		this->setPositionX(this->getPositionX() + m_speed);
		break;
	//case 2:
	//	this->setRotation(90);
	//	this->setPositionY(this->getPositionY() - m_speed);
	//	break;
	case 3:
		this->setRotation(-180);
		this->setPositionX(this->getPositionX() - m_speed);
		break;
	default:
		break;
	}
	auto wndRect = Rect{ 0, 0, Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height };
	if (!wndRect.containsPoint(this->getPosition()))
	{
		this->removeFromParent();
		static int x = 0;
		x++;
		CCLOG("%d", x);
	}
}

void Bullet::initData(bool b, float speed, int toward)
{
	m_ownToPlayer = b;
	m_speed = speed;
	m_toward = toward;
	if (m_ownToPlayer)
	{
		m_bulletSprite->initWithFile("image2376.png");
	}
	else
	{
		//image1234.png  image1236.png
	}
}