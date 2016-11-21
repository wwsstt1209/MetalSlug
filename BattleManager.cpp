#include "BattleManager.h"

static BattleManager* instance = nullptr;

BattleManager* BattleManager::getInstance()
{
	if (!instance)
	{
		instance = new BattleManager();
	}
	return instance;
}

BattleManager::BattleManager()
{
	m_hero = Hero::create();
}

Hero* BattleManager::getHero()
{
	return m_hero;
}