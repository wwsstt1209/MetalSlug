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