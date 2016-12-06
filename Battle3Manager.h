#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Battle3Manager
{
public:
	static Battle3Manager* getInstance();
	Node* m_bg1;
	Node* m_bg2;
	int m_keyState = 0;
	int m_waveIndex = 0;
	int m_tinyIndex = 0;
	bool m_CreateFinish = 1;
private:
	Battle3Manager() {};
	~Battle3Manager() {};
};