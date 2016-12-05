#pragma once
#include "cocos2d.h"
#include "GameInfo.h"
#include "Bullet.h"
USING_NS_CC;

class Enemy2 :public Node
{
public:
	static Enemy2* create();
	bool init();
	void shoot();
	void update(float dt);
private:
	Sprite* m_sprite = nullptr;
};