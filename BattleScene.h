#pragma once
#include "cocos2d.h"
#include "SceneManager.h"
#include "Hero.h"
#include "AllEnemiesHeadfile.h"
USING_NS_CC;

class BattleScene :public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(BattleScene);
	void pressKeyCallback(EventKeyboard::KeyCode, Event*);
	void releaseKeyCallback(EventKeyboard::KeyCode, Event*);
private:
};