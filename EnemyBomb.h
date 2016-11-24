#include "cocos2d.h"
#include "BattleManager.h"
USING_NS_CC;

class EnemyBomb :public Node
{
public:
	static EnemyBomb* create();
	bool init();
	void update(float dt);
private:
	Sprite* m_bomb = nullptr;
	Sprite* m_umbrella = nullptr;
};