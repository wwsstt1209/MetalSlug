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
	if (m_ownToPlayer == 0)
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
	}
	else if (m_ownToPlayer == 1)
	{
		this->setPosition(Vec2(this->getPositionX() - m_speed * m_speedXY.x, this->getPositionY() - m_speed * m_speedXY.y));
	}
	else if (m_ownToPlayer == 2)
	{
		if (m_speedXY.y > 0)
		{
			this->setPositionY(this->getPositionY() - m_speedXY.y);
			--m_speedXY.y;
		}
		else
		{
			m_speedXY.x += 0.2;
			this->setPositionX(this->getPositionX() - m_speedXY.x);
		}
	}
	else if (m_ownToPlayer == 3)
	{
		this->setPositionY(this->getPositionY() - m_speedXY.y);
	}
	static Rect wndRect = Rect{ 0, 65, Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height };
	if (!wndRect.containsPoint(this->getPosition()))
	{
		BattleManager::getInstance()->vBullet.eraseObject(this);
		this->removeFromParent();
	}
}

void Bullet::initData(int b, float speed, int toward)
{
	m_ownToPlayer = b;
	m_speed = speed;
	m_toward = toward;
	switch (HeroInfo::getInstance()->m_gun)
	{
	case SMALL:
		m_bulletSprite->initWithFile("image2376.png");
		break;
	case MEDIUM:
		m_bulletSprite->initWithFile("image2403.png");
		break;
	case GIANT:
		m_bulletSprite->initWithFile("image2416.png");    // ÓÐÐòÁÐÖ¡
		break;
	}
}

void Bullet::initEnemyBullet(int ownToPlayer, float speed)
{
	if (BattleManager::getInstance()->m_hero)
	{
		m_ownToPlayer = ownToPlayer;
		m_speed = speed;
		auto targetPos = BattleManager::getInstance()->m_hero->getPosition();
		auto XY = Vec2(this->getPositionX() - targetPos.x, this->getPositionY() - targetPos.y);
		auto rateX = XY.x / sqrt((XY.x*XY.x) + (XY.y*XY.y));
		auto rateY = XY.y / sqrt((XY.x*XY.x) + (XY.y*XY.y));
		m_speedXY = Vec2(rateX, rateY);
		if (AnimationCache::getInstance()->getAnimation("enemyBullet") == nullptr)
		{
			Vector<SpriteFrame*>vSf;
			for (int i = 0; i < 3; ++i)
			{
				auto filename = StringUtils::format("image%d.png", 1264 + i * 2);
				vSf.pushBack(SpriteFrame::create(filename, Rect(0, 0, 18, 18)));
			}
			AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vSf, 0.3), "enemyBullet");
		}
		m_bulletSprite->initWithFile("image1264.png");
		m_bulletSprite->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("enemyBullet"))));
	}
	else
	{
		BattleManager::getInstance()->vBullet.eraseObject(this);
		this->removeFromParent();
	}
}

void Bullet::initEnemyPlaneBullet1(int ownToPlayer, float speedY)
{
	m_ownToPlayer = ownToPlayer;
	m_bulletSprite->initWithFile("image720.png");
	m_speedXY = Vec2(0, speedY);
	m_bulletSprite->setFlippedX(1);
}

void Bullet::initEnemyPlaneBullet2(int ownToPlayer, float speedY)
{
	m_ownToPlayer = ownToPlayer;
	m_speedXY = Vec2(0, speedY);
	m_bulletSprite->initWithFile("image1234.png");
	auto callback1 = CallFunc::create([this]()->void{
		m_bulletSprite->initWithFile("image1236.png");
	});
	auto callback2 = CallFunc::create([this]()->void{
		m_bulletSprite->initWithFile("image1234.png");
	});
	m_bulletSprite->runAction(RepeatForever::create(Sequence::create(callback1, DelayTime::create(0.3), callback2, DelayTime::create(0.3), nullptr)));
}