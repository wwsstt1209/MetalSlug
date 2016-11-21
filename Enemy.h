#pragma once 
#include "cocos2d.h"
#include "BattleManager.h"
USING_NS_CC;

class Enemy :public Node
{
public:
	static Enemy* create(int);
	bool init(int);
	void update(float dt);
private:
	int m_type;				//0���� 1ǹ�� 2����� 
	Sprite* m_body;

};