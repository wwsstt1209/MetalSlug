#pragma once
#include "cocos2d.h"
#include "GameInfo.h"
USING_NS_CC;

class EnemyBomb :public Node
{
public:
	static EnemyBomb* create();
	bool init();
	void initWithUmbrella();
	void initBreakTruck();
	void update(float dt);
	void update1(float dt);
	void update2(float dt);
private:
	Sprite* m_bomb = nullptr;
	Sprite* m_umbrella = nullptr;
	int m_type;
};