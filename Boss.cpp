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

	for (int i = 0;i < 10;++i)
	{
		auto fileName = StringUtils::format("boss/%d_1.png", i + 1);
		auto spr = Sprite::create(fileName);
		this->addChild(spr, i);
		m_vSprite.pushBack(spr);
		spr->setPosition(300, 300);
	}

	m_vSprite.at(0)->setPosition(Vec2(-35,-5));
	m_vSprite.at(1)->setPosition(Vec2(35, 20));
	m_vSprite.at(2)->setPosition(Vec2(-125, 110));
	m_vSprite.at(3)->setPosition(Vec2(-150, 35));
	m_vSprite.at(4)->setPosition(Vec2(0, 100));
	m_vSprite.at(5)->setPosition(Vec2(-10, 35));
	m_vSprite.at(6)->setPosition(Vec2(150, 145));
	m_vSprite.at(7)->setPosition(Vec2(100, 50));
	m_vSprite.at(8)->setPosition(Vec2(60, 40));
	m_vSprite.at(9)->setPosition(Vec2(140, 60));

	return 1;
}

void Boss::update(float dt)
{

}

void Boss::breakTruck()
{
	schedule(CC_CALLBACK_0(Boss::breakTruckUpdate, this), 0.8, "breakTruck");
}

void Boss::breakTruckUpdate()
{
	auto bomb = EnemyBomb::create();
	bomb->initBreakTruck();
	BattleManager::getInstance()->battleScene->addChild(bomb, 4);
	bomb->setPosition(this->getPosition());
}