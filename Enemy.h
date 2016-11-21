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
	int m_type;				//0Õì²ì±ø 1Ç¹±ø 2»ð¼ý±ø 
	Sprite* m_body;

};