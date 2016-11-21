#pragma once
#include "cocos2d.h"
#include "StartScene.h"
#include "GuideScene.h"
#include "BattleScene.h"
#include "DeadScene.h"

class SceneManager
{
public:
	static SceneManager* getInstance();
	Scene* getStartScene();
	Scene* getGuideScene();
	Scene* getBattleScene();
	Scene* getDeadScene();
private:
	SceneManager();
	~SceneManager(){};
};