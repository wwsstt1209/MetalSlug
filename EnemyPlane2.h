#include "cocos2d.h"
#include "BattleManager.h"
#include "Bullet.h"
USING_NS_CC;

class EnemyPlane2 :public Node
{
public:
	static EnemyPlane2* create();
	bool init();
	void update(float dt);
	void flyUpdate(float dt);
	void shootUpdate(float dt);
private:
	bool m_screw;
	bool m_moveToRight;
	Sprite* m_airscrew;
	Sprite* m_plane;
};