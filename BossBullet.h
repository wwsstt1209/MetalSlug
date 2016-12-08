#pragma once
#include "cocos2d.h"
#include "GameInfo.h"
USING_NS_CC;

class BossBullet :public Node
{
public:
	static BossBullet* create();
	bool init();
	void setTarget();
	void update(float dt);
private:
	Sprite* m_spr;
	Vec2 m_rateXY;
	float m_speed;
};