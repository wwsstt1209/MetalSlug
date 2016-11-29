#include "SceneManager.h"

static SceneManager* instance = nullptr;

SceneManager* SceneManager::getInstance()
{
	if (!instance)
	{
		instance = new SceneManager();
	}
	return instance;
}

SceneManager::SceneManager()
{
}

Scene* SceneManager::getStartScene()
{
	auto startScene = StartScene::createScene();
	return startScene;
}

Scene* SceneManager::getGuideScene()
{
	auto guideScene = GuideScene::createScene();
	return guideScene;
}

Scene* SceneManager::getBattleScene0()
{
	auto battleScene0 = BattleScene0::createScene();
	return battleScene0;
}

Scene* SceneManager::getDeadScene()
{
	auto deadScene = DeadScene::createScene();
	return deadScene;
}

Scene* SceneManager::getBattleScene1()
{
	auto battleScene1 = BattleScene1::createScene();
	return battleScene1;
}

Scene* SceneManager::getBattleScene2()
{
	auto battleScene2 = BattleScene2::createScene();
	return battleScene2;
}