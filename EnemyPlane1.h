#pragma once
#include "cocos2d.h"
#include "GameInfo.h"
#include "Bullet.h"
USING_NS_CC;

class EnemyPlane1 :public Node
{
public:
	static EnemyPlane1* create();
	bool init();
	void flyUpdate(float dt);
	void shootUpdate(float dt);
private:
	bool m_screw;
	Sprite* m_airscrew;
	Sprite* m_plane;
};