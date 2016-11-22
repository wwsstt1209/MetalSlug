#include "EnemyA.h"

EnemyA* EnemyA::create()
{
	EnemyA* ret = new(std::nothrow) EnemyA();
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

bool EnemyA::init()
{
	if (!EnemyWithGun::init())
	{
		return 0;
	}

	

	return 1;
}

void EnemyA::update(float dt)
{

}