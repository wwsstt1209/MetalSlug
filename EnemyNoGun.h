#pragma once
#include "Enemy.h"

class EnemyNoGun :public Enemy					//����  û��ǹ  ��������->����->��·
{
public:
	static EnemyNoGun* create();
	bool init();
protected:
	Vector<SpriteFrame*>vEscape;
	Vector<SpriteFrame*>vScared;
};