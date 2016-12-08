#pragma once
#include "cocos2d.h"
#include "GameInfo.h"
#include "EnemyBomb.h"
#include "BossBomb.h"
#include "BossBullet.h"
#include "Gear.h"
USING_NS_CC;

class Boss :public Node
{
public:
	static Boss* create();
	bool init();
	void breakTruck();
	void breakTruckUpdate();
	void launchScheduler();
	void update(float dt);
	void shootBullets();
	void launchBombs();
private:
	Vector<Gear*>m_vGears;
	Sprite* m_screw;
	Sprite* m_fire;
	float time = 0;
	bool m_upToDown = 0;
};

//炸弹用EnemyBomb  EnemyBomb重写分类  并重写添加到BattleManager里的vEnemyBomb

//子弹和炸弹的不同对象可以使用不同调度器，减少update内的判断次数

//子弹和炸弹的爆炸后释放

//卡车炸毁后释放