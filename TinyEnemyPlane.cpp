#include "TinyEnemyPlane.h"

TineEnemyPlane* TineEnemyPlane::create()
{
	TineEnemyPlane* ret = new(std::nothrow) TineEnemyPlane();
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

bool TineEnemyPlane::init()
{
	if (!Node::init())
	{
		return 0;
	}
	scheduleUpdate();

	GameInfo::getInstance()->vAirEnemy.pushBack(this);

	m_sprite = Sprite::create("tinyplane/image2977.png");
	this->addChild(m_sprite);

	m_speedMax = -10;


	return 1;
}


void TineEnemyPlane::update(float dt)
{
	this->setPositionX(this->getPositionX() + m_speedMax);
	m_speedMax += 0.09;

	if (this->getPositionX() < 50)
	{
		m_sprite->stopAllActions();
		m_sprite->initWithFile("tinyplane/image2999.png");
	}
	else if (this->getPositionX() >= 50 && this->getPositionX() < 150)
	{
		m_sprite->stopAllActions();
		m_sprite->initWithFile("tinyplane/image2997.png");
	}
	else
	{
		m_sprite->initWithFile("tinyplane/image2977.png");
	}

	if (m_speedMax > 0)
		m_sprite->setFlippedX(1);
	if (m_speedMax > 0 && this->getPositionX() > 560)
	{
		GameInfo::getInstance()->vAirEnemy.eraseObject(this);
		this->removeFromParent();
		return;
	}

	for (int i = 0;i < GameInfo::getInstance()->vHeroBullet.size();++i)
	{
		auto posBulletInPlane = m_sprite->convertToNodeSpace(GameInfo::getInstance()->vHeroBullet.at(i)->getPosition());
		Rect planeRect = { 0,0,m_sprite->getContentSize().width,m_sprite->getContentSize().height };
		if (planeRect.containsPoint(posBulletInPlane))
		{
			GameInfo::getInstance()->vHeroBullet.at(i)->removeFromParent();
			GameInfo::getInstance()->vHeroBullet.erase(i);
			auto release = CallFunc::create([this]()->void {
				GameInfo::getInstance()->vAirEnemy.eraseObject(this);
				this->removeFromParent();
			});
			auto ani = AnimationCache::getInstance()->getAnimation("tinyExplode");
			m_sprite->runAction(Sequence::create(Animate::create(ani), release, nullptr));
			unscheduleUpdate();
		}
		return;
	}
}