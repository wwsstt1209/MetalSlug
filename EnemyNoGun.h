#pragma once
#include "Enemy.h"

class EnemyNoGun :public Enemy					//侦察兵  没有枪  看到主角->惊吓->跑路
{
public:
	static EnemyNoGun* create();
	bool init();
protected:
	Vector<SpriteFrame*>vEscape;
	Vector<SpriteFrame*>vScared;
};