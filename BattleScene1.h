#pragma once
#include "cocos2d.h"
#include "SceneManager.h"
#include "Hero.h"
#include "Enemy.h"
#include "Truck.h"
#include "EnemyPlane1.h"
#include "EnemyPlane2.h"
#include "Boss.h"
USING_NS_CC;

class BattleScene1 :public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt);
	void pressKeyCallback(EventKeyboard::KeyCode, Event*);
	void releaseKeyCallback(EventKeyboard::KeyCode, Event*);
	void createNewEnemyWave();
	void createNewBombWave();
	void escapeFromTruck();
	void runBattleScene2();
	CREATE_FUNC(BattleScene1);
private:
	bool m_startCreateEnemy = 0;
	bool m_sceneEnd = 0;
	int m_timer = 0;
};