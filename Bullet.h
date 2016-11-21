#pragma once 
#include "cocos2d.h"
#include "HeroInfo.h"
USING_NS_CC;

class Bullet :public Node
{
public:
	static Bullet* create();
	bool init();
	void update(float dt);
	void initData(bool ownToPlayer, float speed, int toward);//0123иосробвС
private:
	bool m_ownToPlayer;
	float m_speed;
	int m_toward;
	Sprite* m_bulletSprite;
};