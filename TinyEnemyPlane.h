#pragma once
#include "cocos2d.h"
#include "GameInfo.h"
USING_NS_CC;

class TineEnemyPlane :public Node
{
public:
	static TineEnemyPlane* create();
	bool init();
	void update(float dt);
private:
	float m_speedMax;
	float m_imageIndex;
	Sprite* m_sprite;
};