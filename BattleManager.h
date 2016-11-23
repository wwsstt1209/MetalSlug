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
	Layer* battleScene;
	int m_inBattleNum = 0;
	Sprite* m_Cannon = nullptr;
private:
	BattleManager() {};
	~BattleManager() {};
};