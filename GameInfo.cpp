#include "GameInfo.h"

static GameInfo* instance = nullptr;

GameInfo* GameInfo::getInstance()
{
	if (!instance)
	{
		instance = new GameInfo();
	}
	return instance;
}

GameInfo::GameInfo()
{
	m_score = 0;
	m_heroLife = 9;
}

void GameInfo::heroDead()
{
	--m_heroLife;
}