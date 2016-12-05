#include "Tank.h"

Tank* Tank::create()
{
	Tank* ret = new(std::nothrow) Tank();
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

bool Tank::init()
{
	if (!Node::init())
	{
		return 0;
	}
	scheduleUpdate();

	m_0 = Sprite::create("image2908.png");
	this->addChild(m_0);
	m_1 = Sprite::create("image2910.png");
	this->addChild(m_1);
	m_2 = Sprite::create("image2915.png");
	this->addChild(m_2);
	m_3 = Sprite::create("image2913.png");
	this->addChild(m_3);
	m_4 = Sprite::create("image2918.png");
	this->addChild(m_4);

	m_0->setPosition(Vec2(10, -15));
	m_1->setPosition(Vec2(10, 0));
	m_2->setPosition(Vec2(-10, 35));
	m_3->setPosition(Vec2(60, 40));
	m_4->setPosition(Vec2(15, 65));

	m_rect = { -80, -80, 160, 160 };

	auto m3callbakc1 = CallFunc::create([this]()->void{
		m_3->initWithFile("image2913.png");
	});
	auto m3callbakc2 = CallFunc::create([this]()->void{
		m_3->initWithFile("image2921.png");
	});
	m_3->runAction(RepeatForever::create(Sequence::create(m3callbakc1, DelayTime::create(0.1), m3callbakc2, DelayTime::create(0.1), nullptr)));

	scheduleUpdate();
	schedule(CC_CALLBACK_1(Tank::shootUpdate, this), 3, "tankShoot");

	return 1;
}

void Tank::shootUpdate(float dt)
{
	auto posInWorld = this->convertToWorldSpace(Vec2::ZERO);
	auto posInScene = GameInfo::getInstance()->battleScene->convertToNodeSpace(posInWorld);
	if (posInScene.x < 600)
	{
		auto b = Bullet::create();
		b->setPosition(Vec2(-60, 30) + posInScene);
		b->initByTank(5);
	}
}

void Tank::update(float dt)
{
	auto posInWorld = this->convertToWorldSpace(Vec2::ZERO);
	auto posInScene = GameInfo::getInstance()->battleScene->convertToNodeSpace(posInWorld);
	if (posInScene.x < -100)
	{
		GameInfo::getInstance()->vEnemy.eraseObject(this);
		this->removeFromParent();
	}
}