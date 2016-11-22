#pragma once
#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
USING_NS_CC;
using namespace cocostudio;

class Truck :public Node
{
public:
	static Truck* create();
	bool init();
private:
	Armature* m_armature = nullptr;
};