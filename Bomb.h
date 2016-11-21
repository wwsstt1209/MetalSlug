#pragma once 
#include "cocos2d.h"
#include "HeroInfo.h"
USING_NS_CC;

class Bomb :public Node
{
public:
	static Bomb* create();
	bool init();
	void setBombData(float speedUp);
	void update(float dt);
private:
	float m_speedUp;
	bool isFlying;
	Sprite* m_bomb = nullptr;
};