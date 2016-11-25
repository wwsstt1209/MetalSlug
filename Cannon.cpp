#include "Cannon.h"

Cannon* Cannon::create()
{
	Cannon * ret = new (std::nothrow) Cannon();
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

bool Cannon::init()
{
	if (!Node::init())
	{
		return 0;
	}
	scheduleUpdate();

	spr0 = Sprite::create("onCanon/image2012.png");
	spr0->setPosition(Vec2::ZERO);
	this->addChild(spr0);
	spr1 = Sprite::create("onCanon/image2014.png");
	spr1->setPosition(Vec2(0, 40));
	this->addChild(spr1);

	return 1;
}