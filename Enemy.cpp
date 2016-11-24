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
	schedule(CC_CALLBACK_1(Enemy::shootUpdate, this), 5, "enemyShoot");
	scheduleUpdate();

	m_body = Sprite::create("airEnemy/image2885.png");
	this->addChild(m_body);

	BattleManager::getInstance()->vEnemy.pushBack(this);

	return 1;
}

void Enemy::update(float dt)
{
	//移动  
	this->setPosition(this->getPosition() - Vec2(0.6, 0.1));
	//改变方向  
	//被击中  
	//移出地图边缘
	if (this->getPositionX() <= -10)
	{
		BattleManager::getInstance()->vEnemy.eraseObject(this);
		this->removeFromParent();
	}
}

void Enemy::shootUpdate(float dt)
{
	auto b = Bullet::create();
	BattleManager::getInstance()->battleScene->addChild(b, 1);
	b->setPosition(Vec2(-50, -75) + this->getPosition());
	b->initEnemyBullet(2);
}