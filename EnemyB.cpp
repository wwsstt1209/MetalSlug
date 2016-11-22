#include "EnemyB.h"

EnemyB* EnemyB::create()
{
	EnemyB* ret = new(std::nothrow) EnemyB();
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

bool EnemyB::init()
{
	if (!EnemyWithGun::init())
	{
		return 0;
	}



	return 1;
}

void EnemyB::update(float dt)
{

}