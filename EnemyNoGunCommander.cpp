#include "EnemyNoGunCommander.h"

EnemyNoGunCommander* EnemyNoGunCommander::create()
{
	EnemyNoGunCommander* ret = new(std::nothrow) EnemyNoGunCommander();
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

bool EnemyNoGunCommander::init()
{
	if (!EnemyNoGun::init())
	{
		return 0;
	}



	return 1;
}

void EnemyNoGunCommander::update(float dt)
{

}