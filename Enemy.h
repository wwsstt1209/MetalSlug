#pragma once 
#include "cocos2d.h"
USING_NS_CC;

class Enemy :public Node
{
public:
	static Enemy* create();
	bool init();
private:
};