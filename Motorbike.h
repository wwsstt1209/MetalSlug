#pragma once
#include "cocos2d.h"
#include "GameInfo.h"
USING_NS_CC;

class Motorbike :public Node
{
public:
	static Motorbike* create();
	bool init();
	void update(float dt);
	void textureUpdate(float dt);
	void setSpeed(int speed);
private:
	Sprite* m_bike;
	Sprite* m_enemy;
	int m_speed;
};