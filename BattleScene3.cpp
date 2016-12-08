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

	AnimationManager::getInstance()->initBattle3Animation();

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
	GameInfo::getInstance()->m_hero = plane;

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

	auto manager = Battle3Manager::getInstance();
	if (GameInfo::getInstance()->vAirEnemy.size() == 0 && Battle3Manager::getInstance()->m_CreateFinish)
	{
		switch (manager->m_waveIndex)
		{
		case 0:
			Battle3Manager::getInstance()->m_CreateFinish = 0;
			schedule(CC_CALLBACK_0(BattleScene3::createLittlePlaneBtoT, this), 0.5, "littlePlane");
			++manager->m_waveIndex;
			break;
		case 1:
			createBombInAir();
			++manager->m_waveIndex;
			break;
		case 2:
			Battle3Manager::getInstance()->m_CreateFinish = 0;
			schedule(CC_CALLBACK_0(BattleScene3::createLittlePlaneTtoB, this), 0.5, "littlePlane2");
			++manager->m_waveIndex;
			break;
		case 3:
			createBikeEnemyInAir();
			++manager->m_waveIndex;
			break;
		case 4:
			createAirMachineEnemy();
			++manager->m_waveIndex;
			break;
		case 5:
			createBombInAir();
			createAirMachineEnemy();
			++manager->m_waveIndex;
			break;
		case 6:
			createBikeEnemyInAir();
			createAirMachineEnemy();
			++manager->m_waveIndex;
			break;
		case 7:
			createBombInAir();
			createBikeEnemyInAir();
			++manager->m_waveIndex;
			break;
		case 8:
			++manager->m_waveIndex;
			createBoss();
			break;
		case 9:
			unscheduleUpdate();
			//Director::getInstance()->replaceScene();
			break;
		}
	}
}

void BattleScene3::pressKeyCallback(EventKeyboard::KeyCode code, Event* evt)
{
	auto state = &(Battle3Manager::getInstance()->m_keyState);
	auto plane = (Heroplane*)(GameInfo::getInstance()->m_hero);
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
	case EventKeyboard::KeyCode::KEY_J:
		plane->shoot();
		break;
	case EventKeyboard::KeyCode::KEY_L:
		plane->shootBomb();
		break;
	}
}

void BattleScene3::releaseKeyCallback(EventKeyboard::KeyCode code, Event* evt)
{
	auto state = &(Battle3Manager::getInstance()->m_keyState);
	auto plane = (Heroplane*)(GameInfo::getInstance()->m_hero);
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

void BattleScene3::createLittlePlaneBtoT()
{
	auto tiny = TineEnemyPlane::create();
	this->addChild(tiny);
	tiny->setPosition(Vec2(600, 50 + 50*Battle3Manager::getInstance()->m_tinyIndex));
	++Battle3Manager::getInstance()->m_tinyIndex;
	if (Battle3Manager::getInstance()->m_tinyIndex == 7)
	{
		Battle3Manager::getInstance()->m_tinyIndex = 0;
		Battle3Manager::getInstance()->m_CreateFinish = 1;
		unschedule("littlePlane");
	}
}

void BattleScene3::createLittlePlaneTtoB()
{
	auto tiny = TineEnemyPlane::create();
	this->addChild(tiny);
	tiny->setPosition(Vec2(600, 350 - 50 * Battle3Manager::getInstance()->m_tinyIndex));
	++Battle3Manager::getInstance()->m_tinyIndex;
	if (Battle3Manager::getInstance()->m_tinyIndex == 7)
	{
		Battle3Manager::getInstance()->m_tinyIndex = 0;
		Battle3Manager::getInstance()->m_CreateFinish = 1;
		unschedule("littlePlane2");
	}
}

void BattleScene3::createBombInAir()
{
	for (int i = 0; i < 10; ++i)
	{
		auto bomb = EnemyBombInAir::create();
		this->addChild(bomb);
		bomb->setPosition(Vec2(600 + CCRANDOM_0_1() * 500, 50 + CCRANDOM_0_1() * 300));
	}
}

void BattleScene3::createBikeEnemyInAir()
{
	for (int i = 0; i < 5; ++i)
	{
		auto enemy = EnemyInAir::create();
		this->addChild(enemy);
		enemy->setPosition(Vec2(600 + (i + 1) / 2 * 200, 200 + pow(-1, i % 2)*(i + 1) / 2 * 60));
	}
}

void BattleScene3::createAirMachineEnemy()
{
	auto machine = EnemyAirMachine::create();
	this->addChild(machine);
	machine->setPosition(Vec2(650, 400*CCRANDOM_0_1()));
}

void BattleScene3::createBoss()
{
	auto boss = Boss::create();
	this->addChild(boss);
	boss->launchScheduler();
	boss->setScale(0.8);
	GameInfo::getInstance()->m_boss = boss;
	boss->setPosition(Vec2(800, 250));
	boss->runAction(MoveBy::create(2, Vec2(-320, 0)));
}