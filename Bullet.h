#pragma once 
#include "cocos2d.h"
#include "HeroInfo.h"
#include "BattleManager.h"
USING_NS_CC;

class Bullet :public Node
{
public:
	static Bullet* create();
	bool init();
	void update(float dt);
	void initData(int ownToPlayer, float speed, int toward);//0123иосробвС
	void initEnemyBullet(int ownToPlayer, float speed);
	void initEnemyPlaneBullet1(int ownToPlayer, float speedY);
	void initEnemyPlaneBullet2(int ownToPlayer, float speedY);
private:
	int m_ownToPlayer;
	float m_speed;
	int m_toward;
	Sprite* m_bulletSprite;
	Vec2 m_speedXY;
};