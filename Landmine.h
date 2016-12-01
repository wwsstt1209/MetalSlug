#pragma once
#include "cocos2d.h"
#include "GameInfo.h"
USING_NS_CC;

class Landmine :public Node
{
public:
	static Landmine* create();
	bool init();
	void update(float dt);
	void updateSprite(float dt);
	void explode();
	void resetPos();
private:
	Sprite* m_sprite = nullptr;
};