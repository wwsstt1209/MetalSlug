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

void BattleManager::addBullet(Bullet* newBullet)
{
	vBullet.pushBack(newBullet); 
}

void BattleManager::eraseBullet(Bullet* newBullet)
{
	vBullet.eraseObject(newBullet);
}