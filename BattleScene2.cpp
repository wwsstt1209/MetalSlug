#include "BattleScene2.h"

Scene* BattleScene2::createScene()
{
	auto scene = Scene::create();
	auto layer = BattleScene2::create();
	scene->addChild(layer);

	auto heroInfoUI = Sprite::create("ui/image1001.png");				//英雄信息栏
	heroInfoUI->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, heroInfoUI->getContentSize().height / 2 - 5));
	scene->addChild(heroInfoUI);
	GameInfo::getInstance()->m_heroUI = heroInfoUI;

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
	GameInfo::getInstance()->battleScene = this;
	GameInfo::getInstance()->m_inBattleNum = 2;
	loadAllResource();

	auto myHero = Hero::create();			//创建英雄
	myHero->setPosition(Vec2(80, 80));
	this->addChild(myHero, 3);
	myHero->setScaleX(-1);
	myHero->setName("hero");
	GameInfo::getInstance()->m_hero = myHero;

	auto bg1 = Sprite::create("Scene1/image259.jpg");
	bg1->setPosition(visibleSize / 2);
	this->addChild(bg1, -1);
	Battle2Manager::getInstance()->m_bg1 = bg1;

	auto h = Hostage::create();
	h->setPosition(450, 120);
	bg1->addChild(h);
	auto h2 = Hostage::create();
	h2->setPosition(350, 120);
	bg1->addChild(h2);
	
	auto bg2 = Sprite::create("Scene1/image261.jpg");
	bg2->setPosition(Vec2(560, 0) + visibleSize / 2);
	this->addChild(bg2, -1);
	Battle2Manager::getInstance()->m_bg2 = bg2;

	auto lis = EventListenerKeyboard::create();						//键盘监听器
	lis->onKeyPressed = CC_CALLBACK_2(BattleScene2::pressKeyCallback, this);
	lis->onKeyReleased = CC_CALLBACK_2(BattleScene2::releaseKeyCallback, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);

	schedule(CC_CALLBACK_1(BattleScene2::update1, this), 1.0f / 60, "update1");

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

void BattleScene2::loadAllResource()
{
	for (int i = 0; i < 8; ++i)
	{
		auto filename = StringUtils::format("scene1/image%d.jpg", 259 + i * 2);
		Director::getInstance()->getTextureCache()->addImage(filename);
	}

	if (AnimationCache::getInstance()->getAnimation("bomb") == nullptr)		//加载手雷爆炸动画
	{
		auto bombAnimation = Animation::create();
		for (int i = 0; i < 15; ++i)
		{
			auto fileName = StringUtils::format("image%d.png", i * 2 + 20);
			bombAnimation->addSpriteFrameWithFile(fileName);
		}
		AnimationCache::getInstance()->addAnimation(bombAnimation, "bomb");
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy1/EnemyDead.plist");
	if (AnimationCache::getInstance()->getAnimation("dead1") == nullptr)
	{
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

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy1/jiqiangbing.plist");
	if (AnimationCache::getInstance()->getAnimation("enemyStandShoot") == nullptr)
	{
		Vector<SpriteFrame*>vec;
		for (int i = 0; i < 6; ++i)
		{
			auto fileName = StringUtils::format("image%d.png", 549 + i * 2);
			vec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
		}
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vec, 0.1), "enemyStandShoot");
	}
	if (AnimationCache::getInstance()->getAnimation("enemyStand") == nullptr)
	{
		Vector<SpriteFrame*>vec;
		for (int i = 0; i < 2; ++i)
		{
			auto fileName = StringUtils::format("image%d.png", 414 + i * 2);
			vec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
		}
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(vec, 0.5), "enemyStand");
	}
}

void BattleScene2::update1(float dt)
{
	{
		auto hero = GameInfo::getInstance()->m_hero;
		auto bg1 = (Sprite*)Battle2Manager::getInstance()->m_bg1;
		auto bg2 = (Sprite*)Battle2Manager::getInstance()->m_bg2;
		if (hero->getPositionX() + HeroInfo::getInstance()->m_speed > 250 && HeroInfo::getInstance()->m_towardX_state == 1)
		{
			bg1->setPositionX(bg1->getPositionX() - HeroInfo::getInstance()->m_speed);
			bg2->setPositionX(bg2->getPositionX() - HeroInfo::getInstance()->m_speed);
			for (auto b : GameInfo::getInstance()->vEnemyBullet)
			{
				b->setPositionX(b->getPositionX() - HeroInfo::getInstance()->m_speed);
			}
		}
		if (bg1->getPositionX() <= -280 && Battle2Manager::getInstance()->m_bg1_num < 4)
		{
			++Battle2Manager::getInstance()->m_bg1_num;
			bg1->removeAllChildren();
			auto fileName = StringUtils::format("Scene1/image%d.jpg", 259 + 4 * (Battle2Manager::getInstance()->m_bg1_num - 1));
			bg1->initWithFile(fileName);
			bg1->setPositionX(bg2->getPositionX() + 560);
			switch (Battle2Manager::getInstance()->m_bg1_num)
			{
			case 2://3
			{
				auto plane = EnemyPlane2::create();
				GameInfo::getInstance()->battleScene->addChild(plane);
				plane->setPosition(200, 550);
				plane->runAction(MoveBy::create(2, Vec2(0, -200)));

				createBombWave(bg1);
				createLandMines(3, 100, bg1);
				createMotorBike();
			}
				break;
			case 3://5
			{
				createBombWave(bg1);
				createLandMines(3, 100, bg1);
				createMotorBike();

				auto tank = Tank::create();
				bg1->addChild(tank);
				tank->setPosition(450, 100);
			}
				break;
			default:
				break;
			}
		}
		else if (bg2->getPositionX() <= -280 && Battle2Manager::getInstance()->m_bg2_num < 3)
		{
			++Battle2Manager::getInstance()->m_bg2_num;
			bg2->removeAllChildren();
			auto fileName = StringUtils::format("Scene1/image%d.jpg", 261 + 4 * (Battle2Manager::getInstance()->m_bg2_num - 1));
			bg2->initWithFile(fileName);
			bg2->setPositionX(bg1->getPositionX() + 560);
			switch (Battle2Manager::getInstance()->m_bg2_num)
			{
			case 2://4
			{
					auto enemy = Enemy2::create();
					bg2->addChild(enemy);
					enemy->setPosition(300, 100);

					auto enemy2 = Enemy2::create();
					bg2->addChild(enemy2);
					enemy2->setPosition(200, 100);

					auto tank = Tank::create();
					bg2->addChild(tank);
					tank->setPosition(450, 100);

					createMotorBike();
			}
				break;
			case 3://6
			{
				auto enemy = Enemy2::create();
				bg2->addChild(enemy);
				enemy->setPosition(300, 100);

				auto enemy2 = Enemy2::create();
				bg2->addChild(enemy2);
				enemy2->setPosition(200, 100);

				auto plane = EnemyPlane2::create();
				this->addChild(plane);
				plane->setPosition(200, 550);
				plane->runAction(MoveBy::create(2, Vec2(0, -200)));
				
				createMotorBike();
			}
				break;
			default:
				//人质释放
				break;
			}
		}
		else if (bg2->getPositionX() <= -280 && Battle2Manager::getInstance()->m_bg2_num == 3)
		{
			++Battle2Manager::getInstance()->m_bg2_num;

			bg2->removeAllChildren();
			bg2->initWithFile("Scene1/image273.jpg");
			bg2->setPositionX(bg1->getPositionX() + 670);

			auto heroplane = Heroplane::create();
			bg2->addChild(heroplane, 1);
			heroplane->setName("heroplane");
			heroplane->setPosition(400, 120);

			//可以在这加个boss
		}
		if (Battle2Manager::getInstance()->m_bg2_num == 4 && bg1->getPositionX() <= -280)
		{
			auto hero = (Hero*)(GameInfo::getInstance()->m_hero);
			auto posHeroInBg2 = bg2->convertToNodeSpace(hero->getPosition());
			auto heroplane = (Heroplane*)(bg2->getChildByName("heroplane"));
			auto planePosInWorld = heroplane->convertToWorldSpace(Vec2(0, 0));

			unschedule("update1");
			_eventDispatcher->removeEventListenersForTarget(this, 0);

			hero->getIntoHeroPlane();
			auto fake = Sprite::create("heroplane/image1925.png");
			bg2->addChild(fake, 0);
			fake->setFlippedX(1);
			fake->setPosition(posHeroInBg2);
			auto hide = CallFunc::create([fake]()->void{
				fake->removeFromParent();
			});
			fake->runAction(Sequence::create(JumpTo::create(0.8, planePosInWorld + Vec2(0, 5), 80, 1), DelayTime::create(0.7), hide, nullptr));
			heroplane->go();

			bg2->runAction(MoveTo::create(2, Vec2(170, 200)));

			scheduleOnce(CC_CALLBACK_0(BattleScene2::runBattleScene3, this), 4.5, "runBattleScene3");
		}
	}

}

void BattleScene2::createBombWave(Node* n)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < 5; ++i)
	{
		auto bomb = EnemyBomb::create();
		bomb->setVisible(1);
		bomb->initWithUmbrella();
		n->addChild(bomb, 1);
		bomb->setPosition(Vec2(160 + i * 80, 400 + i * 20));
	}
}

void BattleScene2::createMotorBike()
{
	float left = CCRANDOM_0_1();
	if (left >= 0.5)
	{
		auto motor = Motorbike::create();
		this->addChild(motor, 4);
		motor->setPosition(Vec2(-100, 100));
		motor->setScaleX(-1);
		motor->setSpeed(8);
	}
	else
	{
		auto motor = Motorbike::create();
		this->addChild(motor, 4);
		motor->setPosition(Vec2(600, 100));
		motor->setSpeed(-8);
	}
}

void BattleScene2::createLandMines(int number, float startX, Node* n)
{
	for (int i = 0; i < number; ++i)
	{
		auto mine = Landmine::create();
		mine->setPosition(Vec2(startX + i * 100, 70));
		n->addChild(mine);
	}
}

void BattleScene2::runBattleScene3()
{
	GameInfo::getInstance()->vEnemy.clear();
	GameInfo::getInstance()->vEnemyBullet.clear();
	GameInfo::getInstance()->vHeroBullet.clear();
	Director::getInstance()->replaceScene(TransitionProgressInOut::create(1, SceneManager::getInstance()->getBattleScene3()));
}