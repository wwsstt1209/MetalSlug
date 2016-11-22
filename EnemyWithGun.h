#pragma once
#include "Enemy.h"

class EnemyWithGun :public Enemy					//有枪  看到主角-> 射击  近距离刀
{
public:
	static EnemyWithGun* create();
	bool init();
protected:
	Vector<SpriteFrame*>vShoot;
	Vector<SpriteFrame*>vKnife;
};