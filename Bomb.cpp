#include "Bomb.h"

Bomb* Bomb::create()
{
	Bomb * ret = new (std::nothrow) Bomb();
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

bool Bomb::init()
{
	if (!Node::init())
	{
		return 0;
	}
	scheduleUpdate();

	m_bomb = Sprite::create("image377.png");
	if (HeroInfo::getInstance()->m_towardX == RIGHT)
		m_bomb->setRotation(-180);
	this->addChild(m_bomb);

	return 1;
}

void Bomb::setBombData(float speedUp)
{
	m_speedUp = speedUp;
	isFlying = 1;
}

void Bomb::update(float dt)
{
	if (isFlying)
	{
		if (HeroInfo::getInstance()->m_towardX == RIGHT)
		{
			this->setPosition(Vec2(this->getPositionX() + 3, this->getPositionY() + m_speedUp));
			m_bomb->setRotation(m_bomb->getRotation() + 180 * dt * 2);
		}
		else
		{
			this->setPosition(Vec2(this->getPositionX() - 3, this->getPositionY() + m_speedUp));
			m_bomb->setRotation(m_bomb->getRotation() - 180 * dt * 2);
		}
		--m_speedUp;
	}
	//for ()				//判断是否有障碍物
	//{
	//	if ()				//水  台子
	//	{
	//		//爆炸
	//		return;
	//	}
	//}
	if (this->getPositionY() <= Director::getInstance()->getVisibleSize().height / 2)
	{
		if (isFlying)
		{
			auto ani = AnimationCache::getInstance()->getAnimation("bomb");
			ani->setDelayPerUnit(0.05);
			auto releaseCallback = CallFunc::create([this]()->void{
				this->removeFromParent();
			});
			auto flipCallback = CallFunc::create([this]()->void{
				m_bomb->setRotation(0);
			});
			JumpBy* jumpSec = nullptr;
			if (HeroInfo::getInstance()->m_towardX == RIGHT)
				jumpSec = JumpBy::create(0.2, Vec2(10, 0), 5, 1);
			else
				jumpSec = JumpBy::create(0.2, Vec2(-10, 0), 5, 1);
			m_bomb->runAction(Sequence::create(jumpSec, DelayTime::create(0.1), flipCallback, Animate::create(ani), releaseCallback, nullptr));
		}
		isFlying = 0;
	}
}