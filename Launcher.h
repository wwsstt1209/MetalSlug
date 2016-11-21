#pragma once
#include "cocos2d.h"
#include "Bullet.h"
USING_NS_CC;

class Launcher :public Node
{
public:
	static Launcher* create();
	bool init();
	void initData(Layer*, int);
	void shoot(int toward);
private:
	Layer* m_layer;
	int m_level;   //0手枪  1机关枪  2导弹
};