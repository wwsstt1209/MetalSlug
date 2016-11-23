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

	scheduleUpdate();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Director::getInstance()->setContentScaleFactor(1);
	BattleManager::getInstance()->battleScene = this;

	auto bombAnimation = Animation::create();							//加载手雷爆炸动画
	for (int i = 0; i < 15; ++i)
	{
		auto fileName = StringUtils::format("image%d.png", i * 2 + 20);
		bombAnimation->addSpriteFrameWithFile(fileName);
	}
	AnimationCache::getInstance()->addAnimation(bombAnimation, "bomb");
	
	auto backGroud1 = Sprite::create("scene1/image242.jpg");			//背景图
	backGroud1->setPosition(visibleSize / 2);
	backGroud1->setName("bg1");
	this->addChild(backGroud1);

	auto heroInfoUI = Sprite::create("ui/image1001.png");				//英雄信息栏
	heroInfoUI->setPosition(Vec2(visibleSize.width / 2, heroInfoUI->getContentSize().height / 2));
	this->addChild(heroInfoUI);

	auto myHero = Hero::create();				//创建英雄
	myHero->setPosition(Vec2(-150,0) + visibleSize / 5);
	this->addChild(myHero, 2);
	myHero->setScaleX(-1);
	myHero->setName("hero");
	BattleManager::getInstance()->m_hero = myHero;

	auto truck = Truck::create();
	truck->setPosition(Vec2(-50, -45) + visibleSize / 2);
	this->addChild(truck, 1);

	return 1;
}

void BattleScene0::update(float dt)
{
	//Color3B transitColor = { 255, 255, 255 };
	//Director::getInstance()->replaceScene(CCTransitionFade::create(4.0f, SceneManager::getInstance()->getDeadScene(), transitColor));
	static Node* hero = BattleManager::getInstance()->m_hero;

	if (hero->getPositionX() >= Director::getInstance()->getVisibleSize().width + 50)
	{
		Director::getInstance()->replaceScene(TransitionProgressRadialCCW::create(1,SceneManager::getInstance()->getBattleScene1()));
		unscheduleUpdate();
	}
}