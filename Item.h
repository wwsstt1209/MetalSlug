#pragma once 
#include "cocos2d.h"
USING_NS_CC;

class Item :public Node
{
public:
	static Item* create();
	bool init();
private:
};