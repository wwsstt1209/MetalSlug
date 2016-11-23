#pragma once
#include "cocos2d.h"
#include "SceneManager.h"
#include "Hero.h"
#include "Truck.h"
USING_NS_CC;

class BattleScene0 :public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(BattleScene0);
private:
};