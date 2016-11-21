#pragma once
#include "cocos2d.h"
USING_NS_CC;

class StartScene :public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(StartScene);
	void getItemCallback(Ref*);
	void startGameCallback(Ref*);
	void writterCallback(Ref*);
private:
};