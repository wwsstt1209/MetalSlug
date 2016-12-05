#pragma once
#include "cocos2d.h"
#include "StartScene.h"
#include "GuideScene.h"
#include "BattleScene0.h"
#include "BattleScene1.h"
#include "BattleScene2.h"
#include "BattleScene3.h"
#include "DeadScene.h"

#include "Hero.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Truck.h"
#include "Landmine.h"
#include "Motorbike.h"
#include "EnemyPlane1.h"
#include "EnemyPlane2.h"
#include "Boss.h"
#include "Hostage.h"
#include "Heroplane.h"
#include "Tank.h"

class SceneManager
{
public:
	static SceneManager* getInstance();
	Scene* getStartScene();
	Scene* getGuideScene();
	Scene* getBattleScene0();
	Scene* getBattleScene1();
	Scene* getBattleScene2();
	Scene* getBattleScene3();
	Scene* getDeadScene();
private:
	SceneManager();
	~SceneManager(){};
};