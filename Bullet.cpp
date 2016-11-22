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
	if (!Node::init())
	{
		return 0;
	}
	scheduleUpdate();
	m_bulletSprite = Sprite::create();
	m_bulletSprite->setPosition(Vec2::ZERO);
	this->addChild(m_bulletSprite);
	BattleManager::getInstance()->vBullet.pushBack(this);

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
	case 2:
		this->setRotation(90);
		this->setPositionY(this->getPositionY() - m_speed);
		break;
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
		BattleManager::getInstance()->vBullet.eraseObject(this);
		this->removeFromParent();
	}
}

void Bullet::initData(bool b, float speed, int toward)
{
	m_ownToPlayer = b;
	m_speed = speed;
	m_toward = toward;
	if (m_ownToPlayer)
	{
		switch (HeroInfo::getInstance()->m_gun)
		{
		case SMALL:
			m_bulletSprite->initWithFile("image2376.png");
			break;
		case MEDIUM:
			m_bulletSprite->initWithFile("image2403.png");
			break;
		case GIANT:
			m_bulletSprite->initWithFile("image2416.png");    // ”––Ú¡–÷°
			break;
		}
	}
	else
	{
		//image1234.png  image1236.png
	}
}