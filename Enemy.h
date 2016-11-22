#pragma once 
#include "cocos2d.h"
#include "BattleManager.h"
USING_NS_CC;

enum EnemyAction{ E_STAND, E_RUN, E_HIDE };

class Enemy :public Node
{
public:
	static Enemy* create();
	virtual bool init();
	virtual void loadDeadSource();
	virtual void loadSource(){};
protected:
	Sprite* m_body;
	EnemyAction m_action;
	int m_score;
	Vector<SpriteFrame*>vStand;
	Vector<SpriteFrame*>vRun;
	Vector<SpriteFrame*>vDead1;
	Vector<SpriteFrame*>vDead2;
	Vector<SpriteFrame*>vDead3;
	int m_hp;
};