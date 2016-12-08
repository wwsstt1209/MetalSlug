#include "BossBullet.h"

BossBullet* BossBullet::create()
{
	BossBullet* ret = new(std::nothrow) BossBullet();
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

bool BossBullet::init()
{
	if (!Node::init())
	{
		return 0;
	}
	scheduleUpdate();
	GameInfo::getInstance()->vEnemyBullet.pushBack(this);

	m_spr = Sprite::create("enemy2/image973.png");
	this->addChild(m_spr);

	m_speed = 5;

	return 1;
}

void BossBullet::setTarget()
{
	auto targetPos = GameInfo::getInstance()->m_hero->getPosition();
	auto XY = Vec2(this->getPositionX() - targetPos.x, this->getPositionY() - targetPos.y);
	auto rateX = XY.x / sqrt((XY.x*XY.x) + (XY.y*XY.y));
	auto rateY = XY.y / sqrt((XY.x*XY.x) + (XY.y*XY.y));
	m_rateXY = Vec2(rateX, rateY);
}

void BossBullet::update(float dt)
{
	this->setPosition(this->getPosition() - Vec2(m_rateXY.x*m_speed, m_rateXY.y*m_speed));

	auto hero = GameInfo::getInstance()->m_hero;
	auto posBulletInHero = hero->convertToNodeSpace(this->getPosition());
	Rect HeroPlaneRect = { -75, -42, 150, 84 };
	if (HeroPlaneRect.containsPoint(posBulletInHero))
	{
		auto release = CallFunc::create([this]()->void {
			this->removeFromParent();
			GameInfo::getInstance()->vEnemyBullet.eraseObject(this);
		});
		m_spr->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("bossBulletExplode")), release, nullptr));
		unscheduleUpdate();
	}
}