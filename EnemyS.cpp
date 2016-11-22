#include "EnemyS.h"

EnemyS* EnemyS::create()
{
	EnemyS* ret = new(std::nothrow) EnemyS();
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

bool EnemyS::init()
{
	if (!EnemyWithGun::init())
	{
		return 0;
	}



	return 1;
}

void EnemyS::update(float dt)
{

}