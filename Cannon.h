#include "cocos2d.h"
#include "GameInfo.h"
#include "Bullet.h"
USING_NS_CC;

class Cannon: public Node
{
public:
	static Cannon* create();
	bool init();
	void updateCannon(bool left);
	void resetCannon();
	void fire(bool b);
	void fireUpdate();
private:
	Sprite* spr0 = nullptr;
	Sprite* spr1 = nullptr;
	int m_toward = 0;
	bool m_fire = 0;
};