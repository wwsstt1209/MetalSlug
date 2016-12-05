#pragma once
#include "cocos2d.h"
#include "GameInfo.h"
#include "Battle3Manager.h"
#include "Launcher.h"
USING_NS_CC;

class Heroplane :public Node
{
public:
	static Heroplane* create();
	bool init();
	void go();
	void flyInScene3();
	void update(float dt);
private:
	Sprite* m_head;
	Sprite* m_body;
	Sprite* m_iconIN;
	Sprite* m_all;
	Sprite* m_gun;
	float m_speedX;
	float m_speedY;
	float m_rotateSpeed;
	Launcher* m_launcher;
};