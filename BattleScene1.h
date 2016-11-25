#pragma once
#include "cocos2d.h"
#include "SceneManager.h"
#include "Hero.h"
#include "Enemy.h"
#include "Truck.h"
#include "EnemyBomb.h"
USING_NS_CC;

class BattleScene1 :public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(BattleScene1);
	void loadEnemyDeadResource();
	void pressKeyCallback(EventKeyboard::KeyCode, Event*);
	void releaseKeyCallback(EventKeyboard::KeyCode, Event*);
	void createNewEnemyWave();
	void createNewBombWave();
private:
	bool m_startCreateEnemy = 0;
};