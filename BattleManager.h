#pragma once
#include "cocos2d.h"
USING_NS_CC;

class BattleManager
{
public:
	static BattleManager* getInstance();
	Node* m_hero;
	Vector<Node*>vHeroBullet;
	Vector<Node*>vEnemyBullet;
	Vector<Node*>vHeroBomb;
	Vector<Node*>vEnemyBomb;
	Vector<Node*>vEnemy;
	Layer* battleScene;
	int m_inBattleNum;
	int m_airEnemyWave = 0;
	Node* m_Cannon = nullptr;
private:
	BattleManager() {};
	~BattleManager() {};
};