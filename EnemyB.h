#pragma once
#include "EnemyWithGun.h"

class EnemyB :public EnemyWithGun
{
public:
	static EnemyB* create();
	bool init();
	void update(float dt);
private:

};