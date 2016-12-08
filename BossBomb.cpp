#include "BossBomb.h"

BossBomb* BossBomb::create()
{
	BossBomb* ret = new(std::nothrow) BossBomb();
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

bool BossBomb::init()
{
	if (!Node::init())
	{
		return 0;
	}
	scheduleUpdate();
	GameInfo::getInstance()->vEnemyBullet.pushBack(this);
	m_speed = 0;

	m_spr = Sprite::create("BossBomb/image3073.png");
	this->addChild(m_spr, 1);
	m_spr->setFlippedX(1);
	m_smoke = Sprite::create();
	this->addChild(m_smoke, 0);
	m_smoke->setPosition(Vec2(50, 0));
	m_smoke->setRotation(120);

	auto release = CallFunc::create([this]()->void{
		m_smoke->removeFromParent();
	});

	m_smoke->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("bossBombLaunch")), release, nullptr));
	
	return 1;
}

void BossBomb::update(float dt)
{
	m_speed += 0.1;
	auto hero = GameInfo::getInstance()->m_hero;
	if (hero->getPositionY() < this->getPositionY())
	{
		this->setPositionY(this->getPositionY() - 1);
	}
	else
	{
		this->setPositionY(this->getPositionY() + 1);
	}
	this->setPositionX(this->getPositionX() - m_speed);

	auto posBombInHero = hero->convertToNodeSpace(this->getPosition());
	Rect HeroPlaneRect = {-75, -42, 150, 84};
	if (HeroPlaneRect.containsPoint(posBombInHero))
	{
		auto release = CallFunc::create([this]()->void {
			this->removeFromParent();
			GameInfo::getInstance()->vEnemyBullet.eraseObject(this);
		});
		this->setPositionY(this->getPositionY() + 65);
		m_spr->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("bossBombExplode")), release, nullptr));
		unscheduleUpdate();
	}
}