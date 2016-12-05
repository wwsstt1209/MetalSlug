#include "Battle3Manager.h"

static Battle3Manager* ret = nullptr;

Battle3Manager* Battle3Manager::getInstance()
{
	if (!ret)
	{
		ret = new Battle3Manager();
	}
	return ret;
}