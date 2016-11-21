#include "BattleScene.h"

Scene* BattleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BattleScene::create();
	scene->addChild(layer);
	return scene;
}

bool BattleScene::init()
{
	if (!Layer::init())
	{
		return 0;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Director::getInstance()->setContentScaleFactor(1);

	auto backGroud1 = Sprite::create("scene1/image242.jpg");
	backGroud1->setPosition(visibleSize / 2);
	this->addChild(backGroud1);

	auto heroInfoUI = Sprite::create("ui/image1001.png");
	heroInfoUI->setPosition(Vec2(visibleSize.width / 2, heroInfoUI->getContentSize().height / 2));
	this->addChild(heroInfoUI);

	auto myHero = BattleManager::getInstance()->getHero();
	myHero->setPosition(visibleSize / 2);
	myHero->setLayer(this);
	this->addChild(myHero);
	myHero->setName("hero");

	auto lis = EventListenerKeyboard::create();
	lis->onKeyPressed = CC_CALLBACK_2(BattleScene::pressKeyCallback, this);
	lis->onKeyReleased = CC_CALLBACK_2(BattleScene::releaseKeyCallback, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);

	return 1;
}

void BattleScene::update(float dt)
{
	//Color3B transitColor = { 255, 255, 255 };
	//Director::getInstance()->replaceScene(CCTransitionFade::create(4.0f, SceneManager::getInstance()->getDeadScene(), transitColor));
	auto hero = (Hero*)getChildByName("hero");

}

void BattleScene::pressKeyCallback(EventKeyboard::KeyCode code, Event* evt)
{
	auto hero = (Hero*)getChildByName("hero");
	auto heroInfo = HeroInfo::getInstance();
	switch (code)
	{
	case EventKeyboard::KeyCode::KEY_W:
		HeroInfo::getInstance()->m_towardY = UP;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		HeroInfo::getInstance()->m_towardX_state |= 2;
		HeroInfo::getInstance()->m_towardX = LEFT;
		if(heroInfo->m_act != JUMP)
			HeroInfo::getInstance()->m_act = MOVE;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		HeroInfo::getInstance()->m_towardY = DOWN;
		HeroInfo::getInstance()->m_speed = 1;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		HeroInfo::getInstance()->m_towardX_state |= 1;
		HeroInfo::getInstance()->m_towardX = RIGHT;
		if (heroInfo->m_act != JUMP)
			HeroInfo::getInstance()->m_act = MOVE;
		break;
	case EventKeyboard::KeyCode::KEY_J:
		heroInfo->m_isHitting = 1;
		hero->hit();
		break;
	case EventKeyboard::KeyCode::KEY_K:
		if (HeroInfo::getInstance()->m_act != JUMP)
		{
			HeroInfo::getInstance()->m_act = JUMP;
			heroInfo->m_speedUp = 15;
			HeroInfo::getInstance()->m_speed = 2;
		}
		break;
	case EventKeyboard::KeyCode::KEY_L:
		heroInfo->m_isThrowing = 1;
		hero->throwBomb();
		break;
	default:
		break;
	}
}

void BattleScene::releaseKeyCallback(EventKeyboard::KeyCode code, Event* evt)
{
	auto hero = (Hero*)getChildByName("hero");
	switch (code)
	{
	case EventKeyboard::KeyCode::KEY_A:
		HeroInfo::getInstance()->m_towardX_state &= 13;
		if (HeroInfo::getInstance()->m_act != JUMP && HeroInfo::getInstance()->m_towardX_state == 0)
			HeroInfo::getInstance()->m_act = STAND;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		HeroInfo::getInstance()->m_towardX_state &= 14;
		if (HeroInfo::getInstance()->m_act != JUMP && HeroInfo::getInstance()->m_towardX_state == 0)
			HeroInfo::getInstance()->m_act = STAND;
		break;
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_W:
		HeroInfo::getInstance()->m_towardY = NORMAL;
		HeroInfo::getInstance()->m_speed = 2;
		break;
	default:
		break;
	}
}