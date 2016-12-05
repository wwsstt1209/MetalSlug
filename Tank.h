#pragma once
#include "cocos2d.h"
#include "GameInfo.h"
#include "Bullet.h"
USING_NS_CC;

class Tank :public Node
{
public:
	static Tank* create();
	bool init();
	void shootUpdate(float dt);
	void update(float dt);
private:
	Sprite* m_0 = nullptr;
	Sprite* m_1 = nullptr;
	Sprite* m_2 = nullptr;
	Sprite* m_3 = nullptr;
	Sprite* m_4 = nullptr;
	Rect m_rect;
};