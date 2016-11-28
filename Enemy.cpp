#include "Enemy.h"

Enemy* Enemy::create()
{
	Enemy * ret = new (std::nothrow) Enemy();
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

bool Enemy::init()
{
	if (!Node::init())
	{
		return 0;
	}
	schedule(CC_CALLBACK_1(Enemy::shootUpdate, this), 6, "enemyShoot");
	scheduleUpdate();

	m_body = Sprite::create("airEnemy/image2885.png");
	this->addChild(m_body);
	m_shootPoint = Vec2(-50, -75);

	BattleManager::getInstance()->vEnemy.pushBack(this);

	return 1;
}

void Enemy::update(float dt)
{
	//移动  
	this->setPosition(this->getPosition() - Vec2(0.6, 0.2));
	//改变方向  
	if(BattleManager::getInstance()->m_hero)
	{
		float dX = this->getPositionX() - BattleManager::getInstance()->m_hero->getPositionX();
		float dY = this->getPositionY() - BattleManager::getInstance()->m_hero->getPositionY();
		if (dX < 0)
		{
			this->setScaleX(-1);
			m_shootPoint = Vec2(50, -75);
		}
		if (dY < 50)
			m_body->initWithFile("airEnemy/image2891.png");
		else if(dY>=50 && dY<100)
			m_body->initWithFile("airEnemy/image2889.png");
		else if (dY >= 100 && dY < 150)
			m_body->initWithFile("airEnemy/image2887.png");
	}
	//被击中  
	//移出地图边缘
	if (this->getPositionX() <= -50)
	{
		BattleManager::getInstance()->vEnemy.eraseObject(this);
		this->removeFromParent();
	}
}

void Enemy::shootUpdate(float dt)
{
	auto b = Bullet::create();
	BattleManager::getInstance()->battleScene->addChild(b, 1);
	b->setPosition(m_shootPoint + this->getPosition());
	b->initEnemyBullet(1,2);
}