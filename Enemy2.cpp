#include "Enemy2.h"

Enemy2* Enemy2::create()
{
	Enemy2* ret = new(std::nothrow) Enemy2();
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

bool Enemy2::init()
{
	if (!Node::init())
	{
		return 0;
	}



	return 1;
}