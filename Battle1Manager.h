#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Battle1Manager
{
public:
	static Battle1Manager* getInstance();
	int m_airEnemyWave = 0;
	Node* m_Cannon;
private:
	Battle1Manager() {};
	~Battle1Manager() {};
};