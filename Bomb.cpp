#include "Bomb.h"

Bomb* Bomb::create()
{
	Bomb * ret = new (std::nothrow) Bomb();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool Bomb::init()
{
	if (!Node::create())
	{
		return 0;
	}
	scheduleUpdate();

	auto bombSprite = Sprite::create("image377.png");
	this->addChild(bombSprite);

	return 1;
}