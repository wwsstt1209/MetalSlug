#include "Battle1Manager.h"

static Battle1Manager* instance = nullptr;

Battle1Manager* Battle1Manager::getInstance()
{
	if (!instance)
	{
		instance = new Battle1Manager();
	}
	return instance;
}