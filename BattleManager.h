#pragma once
#include "cocos2d.h"
USING_NS_CC;

class BattleManager
{
public:
	static BattleManager* getInstance();
	Node* m_hero;
	Vector<Node*>vBullet;
	Vector<Node*>vEnemy;
	Vector<Node*>vBomb;
	Vector<Node*>vEnemyBomb;
	Layer* battleScene;
	int m_inBattleNum = 0;
	int m_airEnemyWave = 0;
	Node* m_Cannon = nullptr;
private:
	BattleManager() {};
	~BattleManager() {};
};