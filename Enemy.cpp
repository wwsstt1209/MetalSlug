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
	if (!Node::create())
	{
		return 0;
	}
	scheduleUpdate();



	return 1;
}