#include "cocos2d.h"
#include "BattleManager.h"
USING_NS_CC;

class Boss :public Node
{
public:
	static Boss* create();
	bool init();
	void update(float dt);
private:
	Vector<Sprite*>m_vSprite;
};