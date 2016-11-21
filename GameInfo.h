#pragma once

class GameInfo
{
public:
	static GameInfo* getInstance();
	int getScore() { return m_score; };
	int getHeroLife() { return m_heroLife; };
	void heroDead();
private:
	GameInfo();
	~GameInfo() {};
	int m_score;
	int m_heroLife;
};