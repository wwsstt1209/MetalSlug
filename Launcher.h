#pragma once
#include "cocos2d.h"
#include "Bullet.h"
USING_NS_CC;

class Launcher :public Node
{
public:
	static Launcher* create();
	bool init();
	void initData(int gunType);
	void initByHeroPlane();
	void shoot(int toward);
	void showShootEffect(int toward);
private:
	int m_level;   //0手枪  1机关枪  2导弹
	Sprite* shootEffect;
};