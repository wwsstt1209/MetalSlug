#pragma once
#include "cocos2d.h"
#include "GameInfo.h"
USING_NS_CC;

class BossBomb :public Node
{
public:
	static BossBomb* create();
	bool init();
	void update(float dt);
private:
	Sprite* m_spr;
	Sprite* m_smoke;
	float m_speed;
};