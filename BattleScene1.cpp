#include "BattleScene1.h"

Scene* BattleScene1::createScene()
{
	auto scene = Scene::create();
	auto layer = BattleScene1::create();
	scene->addChild(layer);

	auto heroInfoUI = Sprite::create("ui/image1001.png");				//Ó¢ÐÛÐÅÏ¢À¸
	heroInfoUI->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, heroInfoUI->getContentSize().height / 2));
	scene->addChild(heroInfoUI);

	return scene;
}

bool BattleScene1::init()
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
	BattleManager::getInstance()->m_inBattleNum = 1;

	auto backGroud1 = Sprite::create("scene1/image246.jpg");			//±³¾°Í¼
	backGroud1->setPosition(visibleSize / 2);
	backGroud1->setName("bg1");
	this->addChild(backGroud1);

	auto backGround2 = Sprite::create("scene1/image246.jpg");
	backGround2->setPosition(backGroud1->getPosition() + Vec2(backGroud1->getContentSize().width, 0));
	backGround2->setName("bg2");
	this->addChild(backGround2);

	auto myHero = Hero::create();				//´´½¨Ó¢ÐÛ
	myHero->setPosition(Vec2(-120, -30) + visibleSize / 2);
	this->addChild(myHero, 2);
	myHero->setScaleX(-1);
	myHero->setName("hero");
	BattleManager::getInstance()->m_hero = myHero;

	auto truck = Truck::create();				//¿¨³µ
	truck->setPosition(Vec2(-50, -120) + visibleSize / 2);
	this->addChild(truck, 1);

	this->setPositionY(this->getPositionY() - 65);

	auto lis = EventListenerKeyboard::create();						//¼üÅÌ¼àÌýÆ÷
	lis->onKeyPressed = CC_CALLBACK_2(BattleScene1::pressKeyCallback, this);
	lis->onKeyReleased = CC_CALLBACK_2(BattleScene1::releaseKeyCallback, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);

	return 1;
}

void BattleScene1::update(float dt)
{
	//Color3B transitColor = { 255, 255, 255 };
	//Director::getInstance()->replaceScene(CCTransitionFade::create(4.0f, SceneManager::getInstance()->getDeadScene(), transitColor));
	static Node* hero = BattleManager::getInstance()->m_hero;
	{
		static Node* bg1 = this->getChildByName("bg1");
		static Node* bg2 = this->getChildByName("bg2");
		bg1->setPositionX(bg1->getPositionX() - 2);
		bg2->setPositionX(bg2->getPositionX() - 2);
		if (bg1->getPositionX() <= 0 - bg1->getContentSize().width / 2)
		{
			bg1->setPositionX(Director::getInstance()->getVisibleSize().width + bg1->getContentSize().width / 2);
		}
		if (bg2->getPositionX() <= 0 - bg2->getContentSize().width / 2)
		{
			bg2->setPositionX(Director::getInstance()->getVisibleSize().width + bg2->getContentSize().width / 2);
		}
	}
}

void BattleScene1::pressKeyCallback(EventKeyboard::KeyCode code, Event* evt)
{
	auto hero = (Hero*)getChildByName("hero");
	auto heroInfo = HeroInfo::getInstance();
	switch (code)
	{
	case EventKeyboard::KeyCode::KEY_W:
		heroInfo->m_towardY = UP;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		heroInfo->m_towardX_state |= 2;
		heroInfo->m_towardX = LEFT;
		if(heroInfo->m_act != JUMP)
			heroInfo->m_act = MOVE;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		heroInfo->m_towardY = DOWN;
		heroInfo->m_speed = 1;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		heroInfo->m_towardX_state |= 1;
		heroInfo->m_towardX = RIGHT;
		if (heroInfo->m_act != JUMP)
			heroInfo->m_act = MOVE;
		break;
	case EventKeyboard::KeyCode::KEY_J:
		if (!heroInfo->m_isHitting)
		{
			heroInfo->m_isHitting = 1;
			hero->hit();
		}
		break;
	case EventKeyboard::KeyCode::KEY_K:
		if (heroInfo->m_act != JUMP)
		{
			heroInfo->m_act = JUMP;
			heroInfo->m_speedUp = 15;
			heroInfo->m_jumpStartY = hero->getPositionY();
		}
		break;
	case EventKeyboard::KeyCode::KEY_L:
		if (!heroInfo->m_isThrowing)
		{
			heroInfo->m_isThrowing = 1;
			hero->throwBomb();
		}
		break;
	default:
		break;
	}
}

void BattleScene1::releaseKeyCallback(EventKeyboard::KeyCode code, Event* evt)
{
	auto hero = (Hero*)getChildByName("hero");
	switch (code)
	{
	case EventKeyboard::KeyCode::KEY_A:
		HeroInfo::getInstance()->m_towardX_state &= 13;
		if (HeroInfo::getInstance()->m_act != JUMP && HeroInfo::getInstance()->m_towardX_state == 0)
			HeroInfo::getInstance()->m_act = HeroAction::STAND;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		HeroInfo::getInstance()->m_towardX_state &= 14;
		if (HeroInfo::getInstance()->m_act != JUMP && HeroInfo::getInstance()->m_towardX_state == 0)
			HeroInfo::getInstance()->m_act = HeroAction::STAND;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		HeroInfo::getInstance()->m_speed = 2;
		HeroInfo::getInstance()->m_towardY = NORMAL;
		break;
	case EventKeyboard::KeyCode::KEY_W:
		HeroInfo::getInstance()->m_towardY = NORMAL;
		break;
	default:
		break;
	}
}