#pragma once
#include "cocos2d.h"
#include "Item.h"
#include "GameInfo.h"
#include "cocostudio\CocoStudio.h"
using namespace cocostudio;
USING_NS_CC;

class Hostage :public Node
{
public:
	static Hostage* create();
	bool init();
	void update(float dt);
private:
	Armature* m_armature = nullptr;
};