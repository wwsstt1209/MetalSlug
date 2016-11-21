#pragma once
#include "cocos2d.h"
#include "Launcher.h"
#include "Bomb.h"
#include "HeroInfo.h"
#include "cocostudio\CocoStudio.h"
USING_NS_CC;
using namespace cocostudio;

class Hero :public Node
{
public:
	static Hero* create();
	bool init();
	void update(float dt);
	void jump();
	void hit();
	void throwBomb();
	void setLayer(Layer*);
	void armatureCallback(Armature *armature, MovementEventType movementType, const std::string& movementID);
private:
	Armature* m_armature = nullptr;
	Launcher* m_launcher = nullptr;
	Layer* m_layer;
};