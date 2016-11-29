#include "BattleScene0.h"

Scene* BattleScene0::createScene()
{
	auto scene = Scene::create();
	auto layer = BattleScene0::create();
	scene->addChild(layer);
	return scene;
}

bool BattleScene0::init()
{
	if (!Layer::init())
	{
		return 0;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Director::getInstance()->setContentScaleFactor(1);
	BattleManager::getInstance()->battleScene = this;
	BattleManager::getInstance()->m_inBattleNum = 0;
	
	auto backGroud1 = Sprite::create("scene1/image242.jpg");			//±³¾°Í¼
	backGroud1->setPosition(visibleSize / 2);
	backGroud1->setName("bg1");
	this->addChild(backGroud1);

	auto heroInfoUI = Sprite::create("ui/image1001.png");				//Ó¢ÐÛÐÅÏ¢À¸
	heroInfoUI->setPosition(Vec2(visibleSize.width / 2, heroInfoUI->getContentSize().height / 2));
	this->addChild(heroInfoUI);

	auto myHero = Hero::create();				//´´½¨Ó¢ÐÛ
	myHero->setPosition(Vec2(-150,0) + visibleSize / 5);
	this->addChild(myHero, 2);
	myHero->setScaleX(-1);
	myHero->setName("hero");
	myHero->getIntoTruck();
	BattleManager::getInstance()->m_hero = myHero;

	auto truck = Truck::create();
	truck->setPosition(Vec2(-50, -45) + visibleSize / 2);
	this->addChild(truck, 1);

	scheduleUpdate();

	return 1;
}

void BattleScene0::update(float dt)
{
	//Color3B transitColor = { 255, 255, 255 };
	//Director::getInstance()->replaceScene(CCTransitionFade::create(4.0f, SceneManager::getInstance()->getDeadScene(), transitColor));
	Node* hero = BattleManager::getInstance()->m_hero;

	if (hero->getPositionX() >= Director::getInstance()->getVisibleSize().width + 50)
	{
		unscheduleUpdate();
		hero->removeFromParent();
		Director::getInstance()->replaceScene(TransitionProgressRadialCCW::create(1,SceneManager::getInstance()->getBattleScene1()));
	}
}