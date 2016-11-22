#pragma once
#include "EnemyWithGun.h"

class EnemyS : public EnemyWithGun
{
public:
	static EnemyS* create();
	bool init();
	void update(float dt);
private:

};