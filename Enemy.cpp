#include "Enemy.h"

Enemy* Enemy::create(int type)
{
	Enemy * ret = new (std::nothrow) Enemy();
	if (ret && ret->init(type))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool Enemy::init(int type)
{
	if (!Node::init())
	{
		return 0;
	}
	scheduleUpdate();
	m_type = type;

	switch (m_type)
	{
	case 0:
		m_body = Sprite::create("image407.png");
		break;
	case 1:
		m_body = Sprite::create("image414.png");
		break;
	case 2:
		m_body = Sprite::create("image419.png");
		break;
	default:
		break;
	}

	return 1;
}

void Enemy::update(float dt)
{
	switch (m_type)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
}