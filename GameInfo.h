#pragma once
#include "cocos2d.h"
USING_NS_CC;

class GameInfo
{
public:
	static GameInfo* getInstance();
	int getScore() { return m_score; };
	int getHeroLife() { return m_heroLife; };
	void heroDead();
	Node* m_hero;
	Node* m_heroUI;
	Node* m_boss;
	Vector<Node*>vHeroBullet;
	Vector<Node*>vEnemyBullet;
	Vector<Node*>vHeroBomb;
	Vector<Node*>vEnemyBomb;
	Vector<Node*>vEnemy;
	Vector<Node*>vAirEnemy;
	Layer* battleScene;
	int m_inBattleNum;
private:
	GameInfo();
	~GameInfo() {};
	int m_score;
	int m_heroLife;
};