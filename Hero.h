#pragma once
#include "cocos2d.h"
#include "Launcher.h"
#include "Bomb.h"
#include "HeroInfo.h"
#include "GameInfo.h"
#include "cocostudio\CocoStudio.h"
USING_NS_CC;
using namespace cocostudio;

class Hero :public Node
{
public:
	static Hero* create();
	bool init();
	void update(float dt);
	void updateCannon(bool left);
	void resetCannon();
	void jump();
	void hit();
	void throwBomb();
	void armatureCallback(Armature *armature, MovementEventType movementType, const std::string& movementID);
	void escapeFromTruck();
	void getIntoTruck();
	void getIntoHeroPlane();
private:
	Armature* m_armature = nullptr;
	Launcher* m_launcher = nullptr;
	Sprite* m_sprite = nullptr;
	int m_toward = 0;
};