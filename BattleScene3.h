#pragma once
#include "cocos2d.h"
#include "SceneManager.h"
#include "Battle3Manager.h"
#include "AnimationManager.h"
USING_NS_CC;

class BattleScene3 :public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt);
	void pressKeyCallback(EventKeyboard::KeyCode, Event*);
	void releaseKeyCallback(EventKeyboard::KeyCode, Event*);
	void createLittlePlaneBtoT();
	void createLittlePlaneTtoB();
	void createBombInAir();
	void createBikeEnemyInAir();
	void createAirMachineEnemy();
	void createBoss();
	CREATE_FUNC(BattleScene3);
private:
};