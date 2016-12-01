#pragma once
#include "cocos2d.h"
#include "Cannon.h"
#include "GameInfo.h"
#include "Battle1Manager.h"
#include "cocostudio\CocoStudio.h"
using namespace cocostudio;
USING_NS_CC;

class Truck :public Node
{
public:
	static Truck* create();
	bool init();
	void updateCannon(bool left);
	void resetCannon();
	void cannonFire(bool b);
private:
	Armature* m_armature = nullptr;
	Cannon* m_cannon = nullptr;
};