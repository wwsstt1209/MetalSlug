#include "cocos2d.h"
#include "BattleManager.h"
#include "Bullet.h"
#include "EnemyBomb.h"
USING_NS_CC;

class Boss :public Node
{
public:
	static Boss* create();
	bool init();
	void update(float dt);
	void breakTruck();
	void breakTruckUpdate();
private:
	Vector<Sprite*>m_vSprite;
};

//ը����EnemyBomb  EnemyBomb��д����  ����д��ӵ�BattleManager���vEnemyBomb

//�ӵ���ը���Ĳ�ͬ�������ʹ�ò�ͬ������������update�ڵ��жϴ���

//�ӵ���ը���ı�ը���ͷ�

//����ը�ٺ��ͷ�