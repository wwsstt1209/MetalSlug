#pragma once
#include "cocos2d.h"
#include "GameInfo.h"
USING_NS_CC;

class EnemyInAir :public Node
{
public:
	static EnemyInAir* create();
	bool init();
	void update(float dt);
private:
	Sprite* m_sprite;
};