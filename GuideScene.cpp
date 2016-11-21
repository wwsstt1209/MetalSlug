#include "GuideScene.h"

Scene* GuideScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GuideScene::create();
	scene->addChild(layer);
	return scene;
}

bool GuideScene::init()
{
	if (!Layer::init())
	{
		return 0;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Director::getInstance()->setContentScaleFactor(1);

	auto backGround = Sprite::create("ui/image2609.jpg");
	backGround->setPosition(visibleSize / 2);
	this->addChild(backGround);

	auto startBtn = MenuItemImage::create("ui/822.png","ui/822Alpha.png",CC_CALLBACK_1(GuideScene::startCallback,this));
	startBtn->setPosition(480, 90);
	auto menu = Menu::create(startBtn, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return 1;
}

void GuideScene::update(float dt)
{

}

void GuideScene::startCallback(Ref*)
{
	Director::getInstance()->replaceScene(CCTransitionCrossFade::create(1, SceneManager::getInstance()->getBattleScene()));
}