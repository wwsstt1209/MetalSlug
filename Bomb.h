#pragma once 
#include "cocos2d.h"
#include "HeroInfo.h"
#include "GameInfo.h"
USING_NS_CC;

class Bomb :public Node			//ÊÖÀ×
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
	bool m_right;
	Vec2 m_startPos;
};