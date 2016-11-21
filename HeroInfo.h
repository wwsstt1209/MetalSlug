#pragma once

enum Act{ STAND, MOVE, JUMP };

enum Gun{ SMALL, MEDIUM, GIANT };

enum TowardX{ LEFT, RIGHT };
enum TowardY { NORMAL, UP, DOWN };

class HeroInfo
{
public:
	static HeroInfo* getInstance();
	int m_score;
	int m_heroLife;
	int m_bombNum;
	Act m_act;
	Gun m_gun;
	TowardX m_towardX;
	TowardY m_towardY;
	char m_towardX_state;
	float m_speed;
	float m_speedUp;
	bool m_isHitting;
	bool m_isThrowing;
	bool m_potHit;
private:
	HeroInfo();
	~HeroInfo() {};
};