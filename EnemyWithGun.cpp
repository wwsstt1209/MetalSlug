#include "EnemyWithGun.h"

EnemyWithGun* EnemyWithGun::create()
{
	EnemyWithGun* ret = new(std::nothrow) EnemyWithGun();
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

bool EnemyWithGun::init()
{
	if (!Enemy::init())
	{
		return 0;
	}



	return 1;
}