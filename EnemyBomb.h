#pragma once
#include "cocos2d.h"
#include "GameInfo.h"
USING_NS_CC;

class EnemyBomb :public Node
{
public:
	static EnemyBomb* create();
	bool init();
	void update(float dt);
	void initWithUmbrella();
	void update1(float dt);
	void initBreakTruck();
	void update2(float dt);
	void initInAir();
	void update3(float dt);
private:
	Sprite* m_bomb = nullptr;
	Sprite* m_umbrella = nullptr;
	int m_type;
};