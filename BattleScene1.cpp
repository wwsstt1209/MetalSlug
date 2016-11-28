#include "BattleScene1.h"

Scene* BattleScene1::createScene()
{
	auto scene = Scene::create();
	auto layer = BattleScene1::create();
	scene->addChild(layer);

	auto heroInfoUI = Sprite::create("ui/image1001.png");				//Ӣ����Ϣ��
	heroInfoUI->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, heroInfoUI->getContentSize().height / 2 - 5));
	scene->addChild(heroInfoUI);

	return scene;
}

bool BattleScene1::init()
{
	if (!Layer::init())
	{
		return 0;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Director::getInstance()->setContentScaleFactor(1);
	BattleManager::getInstance()->battleScene = this;
	BattleManager::getInstance()->m_inBattleNum = 1;
	//loadEnemyDeadResource();

	auto bombAnimation = Animation::create();							//�������ױ�ը����
	for (int i = 0; i < 15; ++i)
	{
		auto fileName = StringUtils::format("image%d.png", i * 2 + 20);
		bombAnimation->addSpriteFrameWithFile(fileName);
	}
	AnimationCache::getInstance()->addAnimation(bombAnimation, "bomb");

	auto backGroud1 = Sprite::create("scene1/image246.jpg");			//����ͼ
	backGroud1->setPosition(visibleSize / 2);
	backGroud1->setName("bg1");
	this->addChild(backGroud1,-1);

	auto backGround2 = Sprite::create("scene1/image246.jpg");
	backGround2->setPosition(backGroud1->getPosition() + Vec2(backGroud1->getContentSize().width, 0));
	backGround2->setName("bg2");
	this->addChild(backGround2,-1);

	auto myHero = Hero::create();				//����Ӣ��
	myHero->setPosition(Vec2(-120, -30) + visibleSize / 2);
	this->addChild(myHero, 5);
	myHero->setScaleX(-1);
	myHero->setName("hero");
	BattleManager::getInstance()->m_hero = myHero;

	auto truck = Truck::create();				//����
	truck->setPosition(Vec2(-50, -120) + visibleSize / 2);
	truck->setName("truck");
	this->addChild(truck, 0);

	this->setPositionY(this->getPositionY() - 65);

	auto lis = EventListenerKeyboard::create();						//���̼�����
	lis->onKeyPressed = CC_CALLBACK_2(BattleScene1::pressKeyCallback, this);
	lis->onKeyReleased = CC_CALLBACK_2(BattleScene1::releaseKeyCallback, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);

	scheduleUpdate();

	auto boss = Boss::create();
	this->addChild(boss,4);
	boss->setPosition(Vec2(300, 200));

	return 1;
}

void BattleScene1::loadEnemyDeadResource()
{
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

void BattleScene1::pressKeyCallback(EventKeyboard::KeyCode code, Event* evt)
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
		if (heroInfo->m_act != ONCANNON)
		{
			heroInfo->m_towardX = LEFT;
			if (heroInfo->m_act != JUMP)
				heroInfo->m_act = MOVE;
		}
		break;
	case EventKeyboard::KeyCode::KEY_S:
		if (heroInfo->m_act != ONCANNON)
		{
			heroInfo->m_towardY = DOWN;
			heroInfo->m_speed = 1;
		}
		break;
	case EventKeyboard::KeyCode::KEY_D:
		heroInfo->m_towardX_state |= 1;
		if (heroInfo->m_act != ONCANNON)
		{
			heroInfo->m_towardX = RIGHT;
			if (heroInfo->m_act != JUMP)
				heroInfo->m_act = MOVE;
		}
		break;
	case EventKeyboard::KeyCode::KEY_J:
		if (heroInfo->m_act != ONCANNON)
		{
			if (!heroInfo->m_isHitting)
			{
				heroInfo->m_isHitting = 1;
				hero->hit();
			}
		}
		else
		{

		}
		break;
	case EventKeyboard::KeyCode::KEY_K:
		if (heroInfo->m_act != JUMP)
		{
			heroInfo->m_act = JUMP;
			heroInfo->m_speedUp = 15;
			auto truck = (Truck*)this->getChildByName("truck");
			truck->resetCannon();
			hero->resetCannon();
		}
		break;
	case EventKeyboard::KeyCode::KEY_L:
		if (!heroInfo->m_isThrowing && heroInfo->m_act != ONCANNON)
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
		if (HeroInfo::getInstance()->m_act != ONCANNON)
		{
			if (HeroInfo::getInstance()->m_act != JUMP && HeroInfo::getInstance()->m_towardX_state == 0)
				HeroInfo::getInstance()->m_act = HeroAction::STAND;
		}
		break;
	case EventKeyboard::KeyCode::KEY_D:
		HeroInfo::getInstance()->m_towardX_state &= 14;
		if (HeroInfo::getInstance()->m_act != ONCANNON)
		{
			if (HeroInfo::getInstance()->m_act != JUMP && HeroInfo::getInstance()->m_towardX_state == 0)
				HeroInfo::getInstance()->m_act = HeroAction::STAND;
		}
		break;
	case EventKeyboard::KeyCode::KEY_S:
		if (HeroInfo::getInstance()->m_act != ONCANNON)
		{
			HeroInfo::getInstance()->m_speed = 2;
			HeroInfo::getInstance()->m_towardY = NORMAL;
		}
		break;
	case EventKeyboard::KeyCode::KEY_W:
		if (HeroInfo::getInstance()->m_act != ONCANNON)
		{
			HeroInfo::getInstance()->m_towardY = NORMAL;
		}
		break;
	default:
		break;
	}
}

void BattleScene1::update(float dt)
{
	//Color3B transitColor = { 255, 255, 255 };
	//Director::getInstance()->replaceScene(CCTransitionFade::create(4.0f, SceneManager::getInstance()->getDeadScene(), transitColor));
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
	if (BattleManager::getInstance()->vEnemy.size() == 0 && !m_startCreateEnemy && !m_sceneEnd)
	{
		m_startCreateEnemy = 1;
		schedule(CC_CALLBACK_0(BattleScene1::createNewEnemyWave, this), 3, "createEnemy");
	}
	if (BattleManager::getInstance()->m_airEnemyWave == 2)
	{
		//�������䵼���ɻ�
		auto plane = EnemyPlane1::create();
		this->addChild(plane, 2);
		plane->setPosition(450, 500);
		plane->runAction(MoveBy::create(2, Vec2(0, -150)));
		++BattleManager::getInstance()->m_airEnemyWave;
	}
	else if (BattleManager::getInstance()->m_airEnemyWave == 5)
	{
		//���������ӵ��ɻ�
		auto plane = EnemyPlane2::create();
		this->addChild(plane, 3);
		plane->setPosition(200, 550);
		plane->runAction(MoveBy::create(2, Vec2(0, -150)));
		++BattleManager::getInstance()->m_airEnemyWave;
	}
	else if (BattleManager::getInstance()->m_airEnemyWave == 7)
	{
		//����ը��
		createNewBombWave();
		++BattleManager::getInstance()->m_airEnemyWave;
	}
	else if (BattleManager::getInstance()->m_airEnemyWave == 9 && BattleManager::getInstance()->vEnemy.size() == 0)
	{
		//����һ���ɻ�ը�ٿ���������P2
		m_sceneEnd = 1;
		unschedule("createEnemy");
		++BattleManager::getInstance()->m_airEnemyWave;
	}
	{
		++m_timer;
		auto truck = (Truck*)this->getChildByName("truck");
		auto hero = (Hero*)this->getChildByName("hero");
		if (HeroInfo::getInstance()->m_towardX_state == 2 && HeroInfo::getInstance()->m_act == ONCANNON && m_timer >= 6)
		{
			truck->updateCannon(1);
			hero->updateCannon(1);
			m_timer = 0;
		}
		if (HeroInfo::getInstance()->m_towardX_state == 1 && HeroInfo::getInstance()->m_act == ONCANNON && m_timer >= 6)
		{
			truck->updateCannon(0);
			hero->updateCannon(0);
			m_timer = 0;
		}
	}
}

void BattleScene1::createNewEnemyWave()
{
	static int wave = 0;
	auto enemy = Enemy::create();
	enemy->setPosition(Vec2(50, 70) + Director::getInstance()->getVisibleSize());
	this->addChild(enemy, 1);
	++wave;
	if (wave == 4)
	{
		wave = 0;
		m_startCreateEnemy = 0;
		unschedule("createEnemy");
		++BattleManager::getInstance()->m_airEnemyWave;
	}
}

void BattleScene1::createNewBombWave()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < 5; ++i)
	{
		auto bomb = EnemyBomb::create();
		this->addChild(bomb,0);
		bomb->setPosition(Vec2(visibleSize.width / 2 - 160 + i * 80, visibleSize.height + 100 + i * 20));
	}
}