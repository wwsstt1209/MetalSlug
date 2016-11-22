#pragma once 
#include "cocos2d.h"
#include "BattleManager.h"
USING_NS_CC;

class Enemy :public Node
{
public:
	static Enemy* create();
	virtual bool init();
	virtual void loadDeadSource();
	virtual void loadSource() {};
protected:
	int m_hp;
	int m_score;
	Sprite* m_body;
	Vector<SpriteFrame*>vStand;
	Vector<SpriteFrame*>vMove;
private:
	Vector<SpriteFrame*>vDead1;
	Vector<SpriteFrame*>vDead2;
	Vector<SpriteFrame*>vDead3;
};