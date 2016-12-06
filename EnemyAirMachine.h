#pragma once
#include "cocos2d.h"
#include "GameInfo.h"
USING_NS_CC;

class EnemyAirMachine :public Node
{
public:
	static EnemyAirMachine* create();
	bool init();
	void update(float dt);
private:
	Sprite* m_sprite;
};