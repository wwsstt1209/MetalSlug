#pragma once
#include "EnemyWithGun.h"

class EnemyA :public EnemyWithGun
{
public:
	static EnemyA* create();
	bool init();
	void update(float dt);
private:

};