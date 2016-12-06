#pragma once 
#include "cocos2d.h"
#include "HeroInfo.h"
#include "GameInfo.h"
USING_NS_CC;

class Bullet :public Node
{
public:
	static Bullet* create();
	bool init();
	void update(float dt);
	void initData(float speed, int toward);//0123иосробвС
	void update0(float dt);
	void initEnemyBullet(float speed);
	void update1(float dt);
	void initEnemyPlaneBullet1(float speedY);
	void update2(float dt);
	void initEnemyPlaneBullet2(float speedY);
	void update3(float dt);
	void initCannonBullet(int toward);
	void update4(float dt);
	void initByTank(float speed);
	void update5(float dt);
	void initEnemy2Bullet(float speedX);
	void update6(float dt);
	void initByHeroPlane(float speed, float radian);
	void update7(float dt);
	void initBombByHeroPlane();
	void update8(float dt);
private:
	bool m_ownToPlayer;
	float m_speed;
	int m_toward;
	Sprite* m_bulletSprite;
	Vec2 m_speedXY;
};