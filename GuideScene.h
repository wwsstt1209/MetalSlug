#pragma once
#include "cocos2d.h"
#include "SceneManager.h"
USING_NS_CC;

class GuideScene :public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(GuideScene);
	void startCallback(Ref*);
private:
};