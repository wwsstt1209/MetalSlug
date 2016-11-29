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

//炸弹用EnemyBomb  EnemyBomb重写分类  并重写添加到BattleManager里的vEnemyBomb

//子弹和炸弹的不同对象可以使用不同调度器，减少update内的判断次数

//子弹和炸弹的爆炸后释放

//卡车炸毁后释放