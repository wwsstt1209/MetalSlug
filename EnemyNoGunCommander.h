#pragma once
#include "EnemyNoGun.h"

class EnemyNoGunCommander :public EnemyNoGun
{
public:
	static EnemyNoGunCommander* create();
	bool init();
	void update(float dt);
};