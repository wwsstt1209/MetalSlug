#pragma once
#include "cocos2d.h"
#include "StartScene.h"
#include "GuideScene.h"
#include "BattleScene0.h"
#include "BattleScene1.h"
#include "BattleScene2.h"
#include "DeadScene.h"

class SceneManager
{
public:
	static SceneManager* getInstance();
	Scene* getStartScene();
	Scene* getGuideScene();
	Scene* getBattleScene0();
	Scene* getBattleScene1();
	Scene* getBattleScene2();
	Scene* getDeadScene();
private:
	SceneManager();
	~SceneManager(){};
};