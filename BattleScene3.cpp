#include "BattleScene3.h"

Scene* BattleScene3::createScene()
{
	auto scene = Scene::create();
	auto layer = BattleScene3::create();
	scene->addChild(layer);

	auto heroInfoUI = Sprite::create("ui/image1001.png");				//Ó¢ÐÛÐÅÏ¢À¸
	heroInfoUI->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, heroInfoUI->getContentSize().height / 2 - 5));
	scene->addChild(heroInfoUI);

	return scene;
}

bool BattleScene3::init()
{
	if (!Layer::init())
	{
		return 0;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Director::getInstance()->setContentScaleFactor(1);
	GameInfo::getInstance()->battleScene = this;
	GameInfo::getInstance()->m_inBattleNum = 3;

	auto lis = EventListenerKeyboard::create();						//¼üÅÌ¼àÌýÆ÷
	lis->onKeyPressed = CC_CALLBACK_2(BattleScene3::pressKeyCallback, this);
	lis->onKeyReleased = CC_CALLBACK_2(BattleScene3::releaseKeyCallback, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);

	auto bg1 = Sprite::create("scene1/image278.jpg");
	this->addChild(bg1, -1);
	bg1->setPosition(visibleSize / 2);
	Battle3Manager::getInstance()->m_bg1 = bg1;

	auto bg2 = Sprite::create("scene1/image280.jpg");
	this->addChild(bg2, -1);
	bg2->setPosition(Vec2(560, 0) + visibleSize / 2);
	Battle3Manager::getInstance()->m_bg2 = bg2;

	auto plane = Heroplane::create();
	this->addChild(plane);
	plane->setPosition(Vec2(80, 200));
	plane->flyInScene3();

	scheduleUpdate();

	return 1;
}

void BattleScene3::update(float dt)
{
	auto bg1 = Battle3Manager::getInstance()->m_bg1;
	auto bg2 = Battle3Manager::getInstance()->m_bg2;
	bg1->setPositionX(bg1->getPositionX() - 1);
	bg2->setPositionX(bg2->getPositionX() - 1);
	if (bg1->getPositionX() <= -280)
		bg1->setPositionX(bg2->getPositionX() + 560);
	else if (bg2->getPositionX() <= -280)
		bg2->setPositionX(bg1->getPositionX() + 560);
}

void BattleScene3::pressKeyCallback(EventKeyboard::KeyCode code, Event* evt)
{
	auto state = &(Battle3Manager::getInstance()->m_keyState);
	switch (code)
	{
	case EventKeyboard::KeyCode::KEY_W:
		(*state) |= 8;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		(*state) |= 4;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		(*state) |= 2;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		(*state) |= 1;
		break;
	}
}

void BattleScene3::releaseKeyCallback(EventKeyboard::KeyCode code, Event* evt)
{
	auto state = &(Battle3Manager::getInstance()->m_keyState);
	switch (code)
	{
	case EventKeyboard::KeyCode::KEY_W:
		(*state) &= 7;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		(*state) &= 11;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		(*state) &= 13;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		(*state) &= 14;
		break;
	}
}