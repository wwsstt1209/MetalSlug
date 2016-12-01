#include "Battle2Manager.h"

static Battle2Manager* ret = nullptr;

Battle2Manager* Battle2Manager::getInstance()
{
	if (!ret)
	{
		ret = new Battle2Manager();
	}
	return ret;
}