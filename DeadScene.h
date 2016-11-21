#pragma once
#include "cocos2d.h"
#include "HeroInfo.h"
#include "SceneManager.h"
USING_NS_CC;

class DeadScene :public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(DeadScene);
	void planeAgainCallback(Ref*);
};