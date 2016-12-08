#pragma once
#include "cocos2d.h"
USING_NS_CC;

class AnimationManager
{
public:
	static AnimationManager* getInstance();
	void initBattle3Animation();
private:
	void initUniversalAnimation();
	void initBossAnimation();
	void initAirBombAnimation();
	void initAirEnemyAnimation();
};