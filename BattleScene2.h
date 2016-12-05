#pragma once
#include "cocos2d.h"
#include "SceneManager.h"
#include "Battle2Manager.h"
USING_NS_CC;

class BattleScene2 :public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update1(float dt);
	void loadAllResource();
	void pressKeyCallback(EventKeyboard::KeyCode, Event*);
	void releaseKeyCallback(EventKeyboard::KeyCode, Event*);
	void createBombWave(Node*);
	void createMotorBike();
	void createLandMines(int number, float startX, Node* n);
	CREATE_FUNC(BattleScene2);
};