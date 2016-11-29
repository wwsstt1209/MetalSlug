#include "cocos2d.h"
#include "Hero.h"
#include "BattleManager.h"
USING_NS_CC;

class BattleScene2 :public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt);
	void loadResource();
	void pressKeyCallback(EventKeyboard::KeyCode, Event*);
	void releaseKeyCallback(EventKeyboard::KeyCode, Event*);
	CREATE_FUNC(BattleScene2);
};