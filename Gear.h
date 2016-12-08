#pragma once
#include "cocos2d.h"
#include "GameInfo.h"
#include <iostream>
#include <string>
USING_NS_CC;

class Gear :public Node
{
public:
	static Gear* create(std::string& fileName);
	bool init(std::string& fileName);
	Sprite* getSprite();
	void hit();
	bool resetTexture();
	bool tryToRemove();
private:
	Sprite* m_spr;
	int m_hp;
};