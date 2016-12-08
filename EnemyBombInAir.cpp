#include "EnemyBombInAir.h"

EnemyBombInAir* EnemyBombInAir::create()
{
	EnemyBombInAir* ret = new(std::nothrow) EnemyBombInAir();
	if (ret&&ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool EnemyBombInAir::init()
{
	if (!Node::init())
	{
		return 0;
	}
	GameInfo::getInstance()->vAirEnemy.pushBack(this);

	m_sprite = Sprite::create("image3083.png");
	this->addChild(m_sprite);

	scheduleUpdate();

	return 1;
}

void EnemyBombInAir::update(float dt)
{
	this->setPositionX(this->getPositionX() - 1);
	m_sprite->setRotation(m_sprite->getRotation() - 10.0f * dt);
	auto hero = GameInfo::getInstance()->m_hero;
	auto posHeroInBomb = this->convertToNodeSpace(hero->getPosition());
	Rect bombRect = { 0,0,m_sprite->getContentSize().width,m_sprite->getContentSize().height };
	for (int i = 0;i < GameInfo::getInstance()->vHeroBullet.size();++i)
	{
		auto posBulletInBomb = m_sprite->convertToNodeSpace(GameInfo::getInstance()->vHeroBullet.at(i)->getPosition());
		if (bombRect.containsPoint(posBulletInBomb))
		{
			GameInfo::getInstance()->vHeroBullet.at(i)->removeFromParent();
			GameInfo::getInstance()->vHeroBullet.erase(i);
			m_sprite->setRotation(0);
			auto release = CallFunc::create([this]()->void {
				this->removeFromParent();
				GameInfo::getInstance()->vAirEnemy.eraseObject(this);
			});
			m_sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("eBombExplode")), release, nullptr));
			unscheduleUpdate();
		}
	}
	if (fabs(m_sprite->getPositionX() - posHeroInBomb.x) <= 90 && fabs(m_sprite->getPositionY() - posHeroInBomb.y) <= 50)
	{
		m_sprite->setRotation(0);
		auto release = CallFunc::create([this]()->void {
			this->removeFromParent();
			GameInfo::getInstance()->vAirEnemy.eraseObject(this);
		});
		m_sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("eBombExplode")), release, nullptr));
		unscheduleUpdate();
	}
	if (this->getPositionX() <= -100)
	{
		unscheduleUpdate();
		this->removeFromParent();
		GameInfo::getInstance()->vAirEnemy.eraseObject(this);
	}
}