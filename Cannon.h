#include "cocos2d.h"
#include "BattleManager.h"
USING_NS_CC;

class Cannon: public Node
{
public:
	static Cannon* create();
	bool init();
	void updateCannon(bool left);
	void resetCannon();
private:
	Sprite* spr0 = nullptr;
	Sprite* spr1 = nullptr;
	int m_toward = 0;
};