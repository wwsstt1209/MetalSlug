#include "Heroplane.h"

Heroplane* Heroplane::create()
{
	Heroplane* ret = new(std::nothrow) Heroplane();
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

bool Heroplane::init()
{
	if (!Node::init())
	{
		return 0;
	}

	m_head = Sprite::create("heroplane/image1978.png");
	this->addChild(m_head);
	m_head->setPosition(-25, 35);
	m_head->setRotation(-120);

	m_body = Sprite::create("heroplane/image1979.png");
	this->addChild(m_body);

	m_iconIN = Sprite::create("heroplane/image1974.png");
	this->addChild(m_iconIN);
	m_iconIN->setPosition(0, 80);
	m_iconIN->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5, Vec2(0, 10)), MoveBy::create(0.5, Vec2(0, -10)), nullptr)));

	m_all = Sprite::create("heroplane/image1912.png");
	this->addChild(m_all);
	m_all->setVisible(0);
	m_all->setPosition(this->getPosition());

	m_gun = Sprite::create("heroplane/image1915.png");
	this->addChild(m_gun);
	m_gun->setVisible(0);
	m_gun->setPosition(this->getPosition() + Vec2(0, 2));
	m_gun->setAnchorPoint(Vec2(0.2, 0.5));

	return 1;
}

void Heroplane::go()
{
	m_iconIN->setVisible(0);
	m_head->runAction(Sequence::create(DelayTime::create(1), Spawn::create(RotateBy::create(0.5, 120), MoveBy::create(0.5, Vec2(25, -10))), nullptr));

	auto change = CallFunc::create([this]()->void{
		m_head->removeFromParent();
		m_body->removeFromParent();
		m_all->setVisible(1);
		m_gun->setVisible(1);
	});
	this->runAction(Sequence::create(DelayTime::create(1.5), change, MoveBy::create(0.5, Vec2(20, 0)), Spawn::create(RotateBy::create(1, -35), MoveBy::create(2, Vec2(600, 300))), nullptr));
}

void Heroplane::flyInScene3()
{
	m_iconIN->removeFromParent();
	m_head->removeFromParent();
	m_body->removeFromParent();
	m_all->setVisible(1);
	m_gun->setVisible(1);
	//m_launcher = Launcher::create();
	m_speedX = 3;
	m_speedY = 2;
	m_rotateSpeed = 2;

	scheduleUpdate();
}

void Heroplane::update(float dt)
{
	auto state = Battle3Manager::getInstance()->m_keyState;
	if (state >> 3)
	{
		if (this->getPositionY() + m_speedY <= 400)
			this->setPositionY(this->getPositionY() + m_speedY);
		if(!(state & 1) && !((state & 3) >> 1))
			m_gun->setRotation(m_gun->getRotation() - m_rotateSpeed);
	}
	if ((state & 7) >> 2)
	{
		if (this->getPositionY() - m_speedY >= 0)
			this->setPositionY(this->getPositionY() - m_speedY);
		if (!(state & 1) && !((state & 3) >> 1))
			m_gun->setRotation(m_gun->getRotation() + m_rotateSpeed);
	}
	if ((state & 3) >> 1)
	{
		if (this->getPositionX() - m_speedX >= 0)
			this->setPositionX(this->getPositionX() - m_speedX);
		m_gun->setRotation(m_gun->getRotation() - m_rotateSpeed);
	}
	if ((state & 1))
	{
		if (this->getPositionX() + m_speedX <= 560)
			this->setPositionX(this->getPositionX() + m_speedX);
		m_gun->setRotation(m_gun->getRotation() + m_rotateSpeed);
	}
}