#pragma once
#include "EnemyNoGun.h"

class EnemyNoGunCommon :public EnemyNoGun
{
public:
	static EnemyNoGunCommon* create();
	bool init();
	void update(float dt);
};