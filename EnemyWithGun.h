#pragma once
#include "Enemy.h"

class EnemyWithGun :public Enemy					//��ǹ  ��������-> ���  �����뵶
{
public:
	static EnemyWithGun* create();
	bool init();
protected:
	Vector<SpriteFrame*>vShoot;
	Vector<SpriteFrame*>vKnife;
};