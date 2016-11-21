#pragma once
#include "Hero.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Item.h"
#include "cocos2d.h"

class BattleManager
{
public:
	static BattleManager* getInstance();
	Hero* getHero();
	void addBullet(Bullet* newBullet);
	void eraseBullet(Bullet* newBullet);
private:
	BattleManager();
	~BattleManager() {};
	Hero* m_hero;
	Vector<Bullet*>vBullet;
};