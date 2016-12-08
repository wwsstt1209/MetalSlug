#include "Boss.h"

Boss* Boss::create()
{
	Boss* ret = new(std::nothrow) Boss();
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

bool Boss::init()
{
	if (!Node::init())
	{
		return 0;
	}

	for (int i = 0; i < 3; ++i)
	{
		auto file = StringUtils::format("boss/gear%d_0.png", i);
		auto gear = Gear::create(file);
		this->addChild(gear->getSprite());
		m_vGears.pushBack(gear);
	}
	m_vGears.at(0)->getSprite()->setPosition(Vec2(-100, 80));
	m_vGears.at(1)->getSprite()->setPosition(Vec2(20, -20));
	m_vGears.at(2)->getSprite()->setPosition(Vec2(100, 0));

	m_screw = Sprite::create("boss/9_1.png");
	m_vGears.at(2)->getSprite()->addChild(m_screw);
	m_screw->setAnchorPoint(Vec2(0.1, 0.5));
	m_screw->setPosition(Vec2(120, 200));

	m_fire = Sprite::create("boss/8_2.png");
	m_vGears.at(0)->getSprite()->addChild(m_fire);
	m_fire->setPosition(Vec2(18, 10));
	m_fire->setFlippedX(1);
	m_fire->setScale(0.6);
	m_fire->setVisible(0);

	auto fly = CallFunc::create([this]()->void{
		auto scale = m_screw->getScaleX();
		if (scale == 1)
		{
			m_screw->setScaleX(-1);
		}
		else if (scale == -1)
		{
			m_screw->setScaleX(1);
		}
	});

	m_screw->runAction(RepeatForever::create(Sequence::create(DelayTime::create(0.01), fly, nullptr)));

	return 1;
}

void Boss::breakTruck()
{
	schedule(CC_CALLBACK_0(Boss::breakTruckUpdate, this), 0.8, "breakTruck");
}

void Boss::breakTruckUpdate()
{
	auto bomb = EnemyBomb::create();
	bomb->initBreakTruck();
	GameInfo::getInstance()->battleScene->addChild(bomb, 4);
	bomb->setPosition(this->getPosition());
}

void Boss::launchScheduler()
{
	GameInfo::getInstance()->vAirEnemy.pushBack(this);
	scheduleUpdate();
	schedule(CC_CALLBACK_0(Boss::launchBombs, this), 7, "bossBomb");
	schedule(CC_CALLBACK_0(Boss::shootBullets, this), 2.5, "bossShoot");
}

void Boss::update(float dt)
{
	if (m_upToDown)
	{
		this->setPositionY(this->getPositionY() - 0.5);
	}
	else
	{
		this->setPositionY(this->getPositionY() + 0.5);
	}

	if (this->getPositionY() >= 350)
	{
		m_upToDown = 1;
	}
	else if (this->getPositionY() <= 50)
	{
		m_upToDown = 0;
	}

	for (int i = 0; i < m_vGears.size(); ++i)
	{
		for (int j = 0; j < GameInfo::getInstance()->vHeroBullet.size(); ++j)
		{
			auto posBulletInGear = m_vGears.at(i)->getSprite()->convertToNodeSpace(GameInfo::getInstance()->vHeroBullet.at(j)->getPosition());
			Rect gearRect = { 0, 0, m_vGears.at(i)->getSprite()->getContentSize().width, m_vGears.at(i)->getSprite()->getContentSize().height };
			if (gearRect.containsPoint(posBulletInGear))
			{
				GameInfo::getInstance()->vHeroBullet.at(j)->removeFromParent();
				GameInfo::getInstance()->vHeroBullet.erase(j);
				m_vGears.at(i)->hit();
				if (m_vGears.at(i)->resetTexture())
				{
					auto fileName = StringUtils::format("boss/gear%d_1.png", m_vGears.at(i)->getSprite()->getTag());
					m_vGears.at(i)->getSprite()->initWithFile(fileName);
				}
				if (m_vGears.at(i)->tryToRemove())
				{
					if (i == 0)
					{
						m_fire = nullptr;
						unschedule("bossShoot");
					}
					if (i == m_vGears.size() - 1)
					{
						m_vGears.clear();
						this->removeFromParent();
						GameInfo::getInstance()->vAirEnemy.eraseObject(this);
						return;
					}
					m_vGears.erase(i);
				}
				return;
			}
		}
	}
}

void Boss::shootBullets()
{
	if (m_fire)
	{
		m_fire->runAction(Sequence::create(CallFunc::create([this]()->void {m_fire->setVisible(1);}),
			DelayTime::create(0.05),
			CallFunc::create([this]()->void {m_fire->setVisible(0);}), nullptr));
	}

	auto b = BossBullet::create();
	GameInfo::getInstance()->battleScene->addChild(b);
	b->setPosition(this->getPosition() + Vec2(-150, 0));
	b->setTarget();
}

void Boss::launchBombs()
{
	auto bomb = BossBomb::create();
	GameInfo::getInstance()->battleScene->addChild(bomb);
	bomb->setPosition(this->getPosition() + Vec2(-20, -20));
}