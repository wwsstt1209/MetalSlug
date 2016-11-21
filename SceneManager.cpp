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

Scene* SceneManager::getBattleScene()
{
	auto battleScene = BattleScene::createScene();
	return battleScene;
}

Scene* SceneManager::getDeadScene()
{
	auto deadScene = DeadScene::createScene();
	return deadScene;
}