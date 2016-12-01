#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Battle2Manager
{
public:
	static Battle2Manager* getInstance();
	Node* m_bg1;
	Node* m_bg2;
	int m_bg1_num = 1;
	int m_bg2_num = 1;
private:
	Battle2Manager() {};
	~Battle2Manager() {};
};