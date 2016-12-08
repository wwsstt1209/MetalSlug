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

//ը����EnemyBomb  EnemyBomb��д����  ����д��ӵ�BattleManager���vEnemyBomb

//�ӵ���ը���Ĳ�ͬ�������ʹ�ò�ͬ������������update�ڵ��жϴ���

//�ӵ���ը���ı�ը���ͷ�

//����ը�ٺ��ͷ�