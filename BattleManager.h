#pragma once
#include "Hero.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Item.h"

class BattleManager
{
public:
	static BattleManager* getInstance();
	Hero* getHero();
private:
	BattleManager();
	~BattleManager() {};
	Hero* m_hero;
};