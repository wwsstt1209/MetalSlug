#pragma once
#include "cocos2d.h"
#include "Cannon.h"
#include "BattleManager.h"
#include "cocostudio\CocoStudio.h"
USING_NS_CC;
using namespace cocostudio;

class Truck :public Node
{
public:
	static Truck* create();
	bool init();
	void updateCannon(bool left);
	void resetCannon();
private:
	Armature* m_armature = nullptr;
	Cannon* m_cannon = nullptr;
};