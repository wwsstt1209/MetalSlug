#pragma once 
#include "cocos2d.h"
#include "BattleManager.h"
#include "Bullet.h"
USING_NS_CC;

class Enemy :public Node
{
public:
	static Enemy* create();
	virtual bool init();
	void update(float dt);
	void shootUpdate(float dt);
protected:
	int m_hp;
	int m_score;
	Sprite* m_body;
private:
};