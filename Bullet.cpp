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

	m_bulletSprite = Sprite::create();
	m_bulletSprite->setPosition(Vec2::ZERO);
	this->addChild(m_bulletSprite);

	scheduleUpdate();

	return 1;
}

void Bullet::update(float dt)
{
	Rect wndRect;
	if(GameInfo::getInstance()->m_inBattleNum == 1)
		wndRect = Rect{ 0, 65, Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height };
	else if(GameInfo::getInstance()->m_inBattleNum == 2)
		wndRect = Rect{ 0, 0, Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height };
	if (!wndRect.containsPoint(this->getPosition()))
	{
		if (m_ownToPlayer)
			GameInfo::getInstance()->vHeroBullet.eraseObject(this);
		else
			GameInfo::getInstance()->vEnemyBullet.eraseObject(this);
		this->removeFromParent();
	}
}

void Bullet::initData(float speed, int toward)
{
	GameInfo::getInstance()->battleScene->addChild(this, 3);
	GameInfo::getInstance()->vHeroBullet.pushBack(this);
	m_ownToPlayer = 0;
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
	schedule(CC_CALLBACK_1(Bullet::update0, this), 1.0f / 60, "heroBullet");
}

void Bullet::initEnemyBullet(float speed)
{
	GameInfo::getInstance()->battleScene->addChild(this, 1);
	GameInfo::getInstance()->vEnemyBullet.pushBack(this);
	if (GameInfo::getInstance()->m_hero)
	{
		m_ownToPlayer = 0;
		m_speed = speed;
		auto targetPos = GameInfo::getInstance()->m_hero->getPosition();
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
		GameInfo::getInstance()->vEnemyBullet.eraseObject(this);
		this->removeFromParent();
	}
	schedule(CC_CALLBACK_1(Bullet::update1, this), 1.0f / 60, "enemyBullet");
}

void Bullet::initEnemyPlaneBullet1(float speedY)
{
	GameInfo::getInstance()->battleScene->addChild(this, 3);
	GameInfo::getInstance()->vEnemyBullet.pushBack(this);
	m_ownToPlayer = 0;
	m_bulletSprite->initWithFile("image720.png");
	m_speedXY = Vec2(0, speedY);
	m_bulletSprite->setFlippedX(1);
	schedule(CC_CALLBACK_1(Bullet::update2, this), 1.0f / 60, "enemyPlane1Bullet");
}

void Bullet::initEnemyPlaneBullet2(float speedY)
{
	GameInfo::getInstance()->battleScene->addChild(this, 3);
	GameInfo::getInstance()->vEnemyBullet.pushBack(this);
	m_ownToPlayer = 0;
	m_speedXY = Vec2(0, speedY);
	m_bulletSprite->initWithFile("image1234.png");
	auto callback1 = CallFunc::create([this]()->void{
		m_bulletSprite->initWithFile("image1236.png");
	});
	auto callback2 = CallFunc::create([this]()->void{
		m_bulletSprite->initWithFile("image1234.png");
	});
	m_bulletSprite->runAction(RepeatForever::create(Sequence::create(callback1, DelayTime::create(0.3), callback2, DelayTime::create(0.3), nullptr)));
	schedule(CC_CALLBACK_1(Bullet::update3, this), 1.0f / 60, "enemyPlane2Bullet");
}

void Bullet::initCannonBullet(int toward)
{
	GameInfo::getInstance()->battleScene->addChild(this, 1);
	GameInfo::getInstance()->vHeroBullet.pushBack(this);
	m_ownToPlayer = 1;
	m_bulletSprite->initWithFile("image2376.png");
	m_toward = toward;
	m_bulletSprite->setRotation((toward - 8)*11.25f);
	m_speed = 6;
	auto rad = CC_DEGREES_TO_RADIANS(toward*11.25);
	auto speedX = sin(rad) * m_speed;
	auto speedY = cos(rad) * m_speed;
	m_speedXY = Vec2(speedX, speedY);
	auto hero = GameInfo::getInstance()->m_hero;
	this->setPosition(Vec2(hero->getPositionX(), hero->getPositionY()) + Vec2(0 + toward * 18, 80 - sqrt(toward*toward) * 10));
	schedule(CC_CALLBACK_1(Bullet::update4, this), 1.0f / 60, "cannonBullet");
}

void Bullet::update0(float dt)
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

void Bullet::update1(float dt)
{
	this->setPosition(Vec2(this->getPositionX() - m_speed * m_speedXY.x, this->getPositionY() - m_speed * m_speedXY.y));
}

void Bullet::update2(float dt)
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

void Bullet::update3(float dt)
{
	this->setPositionY(this->getPositionY() - m_speedXY.y);
}

void Bullet::update4(float dt)
{
	this->setPosition(Vec2(this->getPositionX() + m_speedXY.x, this->getPositionY() + m_speedXY.y));
}

void Bullet::initByTank(float speed)
{
	GameInfo::getInstance()->vEnemyBullet.pushBack(this);
	GameInfo::getInstance()->battleScene->addChild(this, 0);
	m_bulletSprite = Sprite::create("image2969.png");
	m_ownToPlayer = 0;
	auto callback1 = CallFunc::create([this]()->void {
		m_bulletSprite->initWithFile("image2971.png");
	});
	auto callback2 = CallFunc::create([this]()->void {
		m_bulletSprite->initWithFile("image2969.png");
	});
	this->addChild(m_bulletSprite);
	m_bulletSprite->runAction(RepeatForever::create(Sequence::create(callback1, DelayTime::create(0.5), callback2, DelayTime::create(0.5), nullptr)));
	m_speed = speed;
	schedule(CC_CALLBACK_1(Bullet::update5, this), 1.0f / 60, "tankBullet");
}

void Bullet::update5(float dt)
{
	this->setPositionX(this->getPositionX() - m_speed);
}

void Bullet::initEnemy2Bullet(float speedX)
{
	GameInfo::getInstance()->vEnemyBullet.pushBack(this);
	GameInfo::getInstance()->battleScene->addChild(this, 1);
	if (GameInfo::getInstance()->m_hero)
	{
		m_ownToPlayer = 0;
		m_speed = speedX;
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
		GameInfo::getInstance()->vEnemyBullet.eraseObject(this);
		this->removeFromParent();
	}
	schedule(CC_CALLBACK_1(Bullet::update6, this), 1.0f / 60, "enemy2Bullet");
}

void Bullet::update6(float dt)
{
	this->setPositionX(this->getPositionX() + m_speed);
}