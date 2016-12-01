#pragma once
#include "cocos2d.h"
#include "SceneManager.h"
#include "Battle1Manager.h"
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