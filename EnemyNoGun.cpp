#include "EnemyNoGun.h"

EnemyNoGun* EnemyNoGun::create()
{
	EnemyNoGun* ret = new(std::nothrow) EnemyNoGun();
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

bool EnemyNoGun::init()
{
	if (!Enemy::init())
	{
		return 0;
	}



	return 1;
}