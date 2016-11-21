#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"
USING_NS_CC;

Scene* StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

bool StartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Director::getInstance()->setContentScaleFactor(1);

	auto startBackGround = Sprite::create("ui/image52.jpg");
	startBackGround->setPosition(visibleSize / 2);
	this->addChild(startBackGround);

	auto initTitle = CallFunc::create([visibleSize, startBackGround]()->void {
		auto gameTitle = Sprite::create("ui/image1122.png");  //可以变成4399上的样子
		gameTitle->setOpacity(0);  //  !!!!
		gameTitle->setScale(2);
		gameTitle->setPosition(Vec2(0, 100) + visibleSize / 2);
		startBackGround->addChild(gameTitle);
		gameTitle->runAction(Spawn::create(CCScaleTo::create(1,1), CCFadeIn::create(1), nullptr));
	});

	auto continueInit = CallFunc::create([visibleSize, startBackGround, this]()->void {
		auto getItemBtn = MenuItemImage::create("ui/821.png", "ui/821Alpha.png", CC_CALLBACK_1(StartScene::getItemCallback, this));
		getItemBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

		auto startBtn = MenuItemImage::create("ui/827.png", "ui/827Alpha.png", CC_CALLBACK_1(StartScene::startGameCallback, this));
		startBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 70));

		auto writterBtn = MenuItemImage::create("ui/485.png", "ui/485Alpha.png", CC_CALLBACK_1(StartScene::writterCallback, this));
		writterBtn->setPosition(Vec2(80, 35));

		auto menu = Menu::create(getItemBtn, startBtn, writterBtn, nullptr);
		menu->setPosition(Vec2::ZERO);

		startBackGround->addChild(menu, 1);
	}); //设置按钮

	auto continueInit2 = CallFunc::create([visibleSize, startBackGround]()->void {

		auto continueInit3 = CallFunc::create([visibleSize, startBackGround]()->void {

			auto continueInit4 = CallFunc::create([visibleSize, startBackGround]()->void {

				auto continueInit5 = CallFunc::create([visibleSize, startBackGround]()->void {

					auto bullet4 = Sprite::create("ui/image2455.png");
					bullet4->setPosition(Vec2(490, 240));
					startBackGround->addChild(bullet4);
					startBackGround->runAction(Sequence::create(
						MoveBy::create(0.1, Vec2(0, -10)),
						MoveBy::create(0.1, Vec2(0, 10)),
						DelayTime::create(0.2),
						nullptr));
				});

				auto bullet3 = Sprite::create("ui/image2455.png");
				bullet3->setPosition(Vec2(360, 320));
				startBackGround->addChild(bullet3);
				startBackGround->runAction(Sequence::create(
					MoveBy::create(0.1, Vec2(0, -10)),
					MoveBy::create(0.1, Vec2(0, 10)),
					DelayTime::create(0.2),
					continueInit5,
					nullptr));
			});

			auto bullet2 = Sprite::create("ui/image2455.png");
			bullet2->setPosition(Vec2(150, 270));
			startBackGround->addChild(bullet2);
			startBackGround->runAction(Sequence::create(
				MoveBy::create(0.1, Vec2(0, -10)),
				MoveBy::create(0.1, Vec2(0, 10)),
				DelayTime::create(0.2),
				continueInit4,
				nullptr));
		});

		auto bullet1 = Sprite::create("ui/image2455.png");
		bullet1->setPosition(Vec2(80,330));
		startBackGround->addChild(bullet1);
		startBackGround->runAction(Sequence::create(
			MoveBy::create(0.1, Vec2(0, -10)), 
			MoveBy::create(0.1, Vec2(0, 10)), 
			DelayTime::create(0.2), 
			continueInit3,
			nullptr));
	});

	startBackGround->runAction(Sequence::create(
		initTitle, 
		DelayTime::create(1), 
		continueInit, 
		DelayTime::create(0.6), 
		continueInit2, 
		nullptr));

	//auto lis = EventListenerTouchOneByOne::create();
	//lis->onTouchBegan = [visibleSize, startBackGround](Touch* t, Event* e)->bool {
	//	Rect playCommonRect = { 230,177,100,46 };
	//	Rect playHardRect = { 180, 127, 100, 46 };
	//	auto touchPos = startBackGround->convertToNodeSpace(t->getLocation());
	//	if (playCommonRect.containsPoint(touchPos))
	//	{
	//		//CCTransitionMoveInT
	//		Director::getInstance()->replaceScene(TransitionSlideInT::create(0.3, SceneManager::getInstance()->getGuideScene()));
	//		//设置难度
	//	}
	//	if (playHardRect.containsPoint(touchPos))
	//	{
	//		Director::getInstance()->replaceScene(TransitionSlideInT::create(0.3, SceneManager::getInstance()->getGuideScene()));
	//		//设置难度
	//	}
	//	return 1;
	//};
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);

	scheduleUpdate();

	return true;
}

void StartScene::update(float dt)
{
	//关闭声音神马的
}

void StartScene::getItemCallback(Ref* ref)
{

}

void StartScene::startGameCallback(Ref* ref)
{
	Director::getInstance()->replaceScene(TransitionSlideInT::create(0.3, SceneManager::getInstance()->getGuideScene()));
}

void StartScene::writterCallback(Ref* ref)
{

}