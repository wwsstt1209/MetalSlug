#include "BattleScene2.h"

Scene* BattleScene2::createScene()
{
	auto scene = Scene::create();
	auto layer = BattleScene2::create();
	scene->addChild(layer);

	auto heroInfoUI = Sprite::create("ui/image1001.png");				//”¢–€–≈œ¢¿∏
	heroInfoUI->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, heroInfoUI->getContentSize().height / 2 - 5));
	scene->addChild(heroInfoUI);

	return scene;
}

bool BattleScene2::init()
{
	if (!Layer::init())
	{
		return 0;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Director::getInstance()->setContentScaleFactor(1);
	BattleManager::getInstance()->battleScene = this;
	BattleManager::getInstance()->m_inBattleNum = 2;
	loadResource();

	auto myHero = Hero::create();			//¥¥Ω®”¢–€
	myHero->setPosition(Vec2(110, 80));
	this->addChild(myHero, 5);
	myHero->setScaleX(-1);
	myHero->setName("hero");
	BattleManager::getInstance()->m_hero = myHero;

	auto bg = Sprite::create("Scene1/image259.jpg");
	bg->setPosition(visibleSize / 2);
	this->addChild(bg, -1);

	auto lis = EventListenerKeyboard::create();						//º¸≈Ãº‡Ã˝∆˜
	lis->onKeyPressed = CC_CALLBACK_2(BattleScene2::pressKeyCallback, this);
	lis->onKeyReleased = CC_CALLBACK_2(BattleScene2::releaseKeyCallback, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);

	scheduleUpdate();

	return 1;
}

void BattleScene2::pressKeyCallback(EventKeyboard::KeyCode code, Event* evt)
{
	auto hero = (Hero*)getChildByName("hero");
	auto heroInfo = HeroInfo::getInstance();
	switch (code)
	{
	case EventKeyboard::KeyCode::KEY_W:
		if (heroInfo->m_act != ONCANNON)
			heroInfo->m_towardY = UP;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		heroInfo->m_towardX_state |= 2;
		heroInfo->m_towardX = LEFT;
		if (heroInfo->m_act != JUMP)
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

void BattleScene2::releaseKeyCallback(EventKeyboard::KeyCode code, Event* evt)
{
	auto hero = (Hero*)getChildByName("hero");
	switch (code)
	{
	case EventKeyboard::KeyCode::KEY_A:
		HeroInfo::getInstance()->m_towardX_state &= 13;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		HeroInfo::getInstance()->m_towardX_state &= 14;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		HeroInfo::getInstance()->m_speed = 3;
		HeroInfo::getInstance()->m_towardY = NORMAL;
		break;
	case EventKeyboard::KeyCode::KEY_W:
		HeroInfo::getInstance()->m_towardY = NORMAL;
		break;
	default:
		break;
	}
}

void BattleScene2::loadResource()
{
	if (AnimationCache::getInstance()->getAnimation("bomb") == nullptr)		//º”‘ÿ ÷¿◊±¨’®∂Øª≠
	{
		auto bombAnimation = Animation::create();
		for (int i = 0; i < 15; ++i)
		{
			auto fileName = StringUtils::format("image%d.png", i * 2 + 20);
			bombAnimation->addSpriteFrameWithFile(fileName);
		}
		AnimationCache::getInstance()->addAnimation(bombAnimation, "bomb");
	}
	if (AnimationCache::getInstance()->getAnimation("dead1") == nullptr)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy1/EnemyDead.plist");
		Vector<SpriteFrame*>vDead;
		for (int i = 0; i < 11; ++i)
		{
			auto fileName = StringUtils::format("image%d.png", 620 + i * 2);
			vDead.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
		}
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vDead, 0.1), "dead1");
	}

	if (AnimationCache::getInstance()->getAnimation("dead2") == nullptr)
	{
		Vector<SpriteFrame*>vDead;
		for (int i = 0; i < 10; ++i)
		{
			auto fileName = StringUtils::format("image%d.png", 658 + i * 2);
			vDead.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
		}
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vDead, 0.1), "dead2");
	}

	if (AnimationCache::getInstance()->getAnimation("dead3") == nullptr)
	{
		Vector<SpriteFrame*>vDead;
		for (int i = 0; i < 7; ++i)
		{
			auto fileName = StringUtils::format("image%d.png", 643 + i * 2);
			vDead.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
		}
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vDead, 0.1), "dead3");
	}
}

void BattleScene2::update(float dt)
{

}