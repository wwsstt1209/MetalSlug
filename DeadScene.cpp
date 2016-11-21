#include "DeadScene.h"

Scene* DeadScene::createScene()
{
	auto scene = Scene::create();
	auto layer = DeadScene::create();
	scene->addChild(layer);
	return scene;
}

bool DeadScene::init()
{
	if (!Layer::init())
	{
		return 0;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Director::getInstance()->setContentScaleFactor(1);
	scheduleUpdate();

	auto backGround = Sprite::create("ui/image2811.jpg");
	backGround->setPosition(visibleSize / 2);
	this->addChild(backGround);

	auto gameOverLbl = Sprite::create("ui/gameover.png");
	gameOverLbl->setPosition(Vec2(0, 150) + visibleSize / 2);
	this->addChild(gameOverLbl);
	
	auto scoreLbl = Label::create(StringUtils::format("%08d", HeroInfo::getInstance()->m_score),"fonts/Marker Felt.ttf",32);
	scoreLbl->setPosition(Vec2(0, 100) + visibleSize / 2);
	scoreLbl->setAdditionalKerning(5);
	this->addChild(scoreLbl);

	auto playAgainBtn = MenuItemImage::create("ui/486.png", "ui/486Alpha.png", CC_CALLBACK_1(DeadScene::planeAgainCallback, this));
	playAgainBtn->setPosition(Vec2(0, -150) + visibleSize / 2);
	auto menu = Menu::create(playAgainBtn, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return 1;
}

void DeadScene::update(float dt)
{
	//点到playAgainBtn的时候回到StartScene
}

void DeadScene::planeAgainCallback(Ref*)
{
	Director::getInstance()->replaceScene(TransitionMoveInT::create(0.3, SceneManager::getInstance()->getStartScene()));
}