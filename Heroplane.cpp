#include "Heroplane.h"

Heroplane* Heroplane::create()
{
	Heroplane* ret = new(std::nothrow) Heroplane();
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

bool Heroplane::init()
{
	if (!Node::init())
	{
		return 0;
	}

	auto head = Sprite::create("heroplane/image1978.png");
	this->addChild(head);
	head->setPosition(-25, 35);
	head->setRotation(-120);
	auto body = Sprite::create("heroplane/image1979.png");
	this->addChild(body);
	auto iconIN = Sprite::create("heroplane/image1974.png");
	this->addChild(iconIN);
	iconIN->setPosition(0, 80);
	iconIN->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5, Vec2(0, 10)), MoveBy::create(0.5, Vec2(0, -10)), nullptr)));

	return 1;
}