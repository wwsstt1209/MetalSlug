#pragma once
#include "cocos2d.h"
#include "GameInfo.h"
USING_NS_CC;

class EnemyBombInAir :public Node
{
public:
	static EnemyBombInAir* create();
	bool init();
	void update(float dt);
private:
	Sprite* m_sprite;
};