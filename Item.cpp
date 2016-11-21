#include "Item.h"

Item* Item::create()
{
	Item * ret = new (std::nothrow) Item();
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

bool Item::init()
{
	if (!Node::create())
	{
		return 0;
	}
	scheduleUpdate();



	return 1;
}