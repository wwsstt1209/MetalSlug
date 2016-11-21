#include "HeroInfo.h"

static HeroInfo* instance = nullptr;

HeroInfo* HeroInfo::getInstance()
{
	if (!instance)
	{
		instance = new HeroInfo();
	}
	return instance;
}

HeroInfo::HeroInfo()
{
	m_score = 0;
	m_heroLife = 9;
	m_bombNum = 9;
	m_act = STAND;
	m_gun = MEDIUM;
	m_towardX = RIGHT;
	m_towardY = NORMAL;
	m_speed = 3;
	m_towardX_state = 0;
	m_speedUp = 0;
	m_isHitting = 0;
	m_isThrowing = 0;
	m_potHit = 0;
	m_jumpStartY = 0;
}