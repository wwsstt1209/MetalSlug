#include "Hero.h"

Hero* Hero::create()
{
	Hero * ret = new (std::nothrow) Hero();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool Hero::init()
{
	if (!Node::init())
	{
		return 0;
	}
	scheduleUpdate();

	ArmatureDataManager::getInstance()->addArmatureFileInfo("Animations/HeroAnimation/HeroAnimation.ExportJson");
	m_armature = Armature::create("HeroAnimation");
	m_armature->getAnimation()->play("stand_stop_handgun_LR");
	m_armature->setPosition(this->getContentSize() / 2);
	m_armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(Hero::armatureCallback, this));
	this->addChild(m_armature);
	m_armature->setVisible(1);

	m_sprite = Sprite::create("onCanon/image2040.png");
	this->addChild(m_sprite);
	m_sprite->setVisible(0);

	m_launcher = Launcher::create();
	m_launcher->setPosition(Vec2(0,10));
	this->addChild(m_launcher);
	m_launcher->initData((int)(HeroInfo::getInstance()->m_gun));
	
	return 1;
}

void Hero::update(float dt)
{
	auto heroInfo = HeroInfo::getInstance();
	auto movementID = m_armature->getAnimation()->getCurrentMovementID();
	switch (HeroInfo::getInstance()->m_act)
	{
	case STAND:
	{
		if (!heroInfo->m_isHitting && !heroInfo->m_isThrowing)
		{
			if (heroInfo->m_gun == SMALL)
			{
				if (movementID != "stand_stop_handgun_LR" && heroInfo->m_towardY == NORMAL)
					m_armature->getAnimation()->play("stand_stop_handgun_LR");
				else if (movementID != "stand_stop_handgun_UP" && heroInfo->m_towardY == UP)
					m_armature->getAnimation()->play("stand_stop_handgun_UP");
				else if (movementID != "squat_stop_handgun_LR" && heroInfo->m_towardY == DOWN)
					m_armature->getAnimation()->play("squat_stop_handgun_LR");
			}
			else
			{
				//如果是机关枪
				if (movementID != "stand_stop_rushgun_LR" && heroInfo->m_towardY == NORMAL)
					m_armature->getAnimation()->play("stand_stop_rushgun_LR");
				else if (movementID != "stand_stop_rushgun_UP" && heroInfo->m_towardY == UP)
					m_armature->getAnimation()->play("stand_stop_rushgun_UP");
				else if (movementID != "squat_stop_rushgun_LR" && heroInfo->m_towardY == DOWN)
					m_armature->getAnimation()->play("squat_stop_rushgun_LR");
			}
		}
		break;
	}
	case MOVE:
	{
		if (heroInfo->m_towardX_state == 0)
			heroInfo->m_act = STAND;
		if (GameInfo::getInstance()->m_inBattleNum == 1)
		{
			if (heroInfo->m_towardX_state == 1)
			{
				if (this->getPositionX() > 440)
					this->runAction(MoveBy::create(0.5, Vec2(0, -80)));
				else if(this->getPositionX() > 370 && this->getPositionY() > 115 && this->getPositionX() - heroInfo->m_speed <= 370)
					this->runAction(MoveBy::create(0.1, Vec2(0, -55)));
			}
			if (heroInfo->m_towardX_state == 2)
			{
				if (this->getPositionX() < 110)
					this->runAction(MoveBy::create(0.8, Vec2(0, -100)));
				else if(this->getPositionY() < 170 && this->getPositionX() <= 370 && this->getPositionX() >= 110)
					this->setPositionX(371);
			}
		}
		if (heroInfo->m_act != JUMP && !heroInfo->m_isHitting && !heroInfo->m_isThrowing)
		{
			if (heroInfo->m_gun == SMALL)
			{
				if (movementID != "stand_move_handgun_LR" && heroInfo->m_towardY == NORMAL)
					m_armature->getAnimation()->play("stand_move_handgun_LR");
				else if (movementID != "stand_move_handgun_UP" && heroInfo->m_towardY == UP)
					m_armature->getAnimation()->play("stand_move_handgun_UP");
				else if (movementID != "squat_move_handgun_LR" && heroInfo->m_towardY == DOWN)
					m_armature->getAnimation()->play("squat_move_handgun_LR");
			}
			else
			{
				//如果是机关枪
				if (movementID != "stand_move_rushgun_LR" && heroInfo->m_towardY == NORMAL)
					m_armature->getAnimation()->play("stand_move_rushgun_LR");
				else if (movementID != "stand_move_rushgun_UP" && heroInfo->m_towardY == UP)
					m_armature->getAnimation()->play("stand_move_rushgun_UP");
				else if (movementID != "squat_move_rushgun_LR" && heroInfo->m_towardY == DOWN)
					m_armature->getAnimation()->play("squat_move_rushgun_LR");
			}
		}
		break;
	}
	case JUMP:
	{
		m_armature->setVisible(1);
		m_sprite->setVisible(0);
		if (!heroInfo->m_isHitting && !heroInfo->m_isThrowing)
		{
			if (heroInfo->m_gun == SMALL)
			{
				if (movementID != "jump_normal_handgun_LR" && heroInfo->m_isHitting == 0 && heroInfo->m_isThrowing == 0)
					m_armature->getAnimation()->play("jump_normal_handgun_LR");
			}
			else
			{
				//如果是机关枪
				if (movementID != "jump_normal_rushgun_LR" && heroInfo->m_isHitting == 0 && heroInfo->m_isThrowing == 0)
					m_armature->getAnimation()->play("jump_normal_rushgun_LR");
			}
		}
		jump();
	}
	break;
	case ONCANNON:
	{
		m_armature->setVisible(0);
		m_sprite->setVisible(1);
	}
		break;
	default:
		break;
	}

	if (heroInfo->m_towardX_state == 2)
	{
		if (heroInfo->m_act != ONCANNON)
		{
			this->setScaleX(1);
			if (GameInfo::getInstance()->m_inBattleNum == 2)
			{
				if (this->getPositionX() - heroInfo->m_speed < 30)
					return;
			}
			this->setPositionX(this->getPositionX() - heroInfo->m_speed);
		}
	}
	if (heroInfo->m_towardX_state == 1)
	{
		if (heroInfo->m_act != ONCANNON)
		{
			this->setScaleX(-1);
			if (GameInfo::getInstance()->m_inBattleNum == 2)
			{

				if (this->getPositionX() + heroInfo->m_speed > 250)
					return;
			}
			this->setPositionX(this->getPositionX() + heroInfo->m_speed);
		}
	}

	Rect wndRect;
	if (GameInfo::getInstance()->m_inBattleNum == 1)
		wndRect = { 0, 60, Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height };
	else
		wndRect = { 0, 0, Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height };
	if (!wndRect.containsPoint(this->getPosition()) && GameInfo::getInstance()->m_inBattleNum)
	{
		this->stopAllActions();
		GameInfo::getInstance()->m_hero = nullptr;
		this->removeFromParent();
	}
}

void Hero::jump()
{
	auto heroInfo = HeroInfo::getInstance();
	this->setPositionY(this->getPositionY() + heroInfo->m_speedUp);
	--heroInfo->m_speedUp;

	if (GameInfo::getInstance()->m_inBattleNum == 1)
	{
		float height = 0;
		if (this->getPositionX() >= 110 && this->getPositionX() < 368)
			height = 170;
		else if (this->getPositionX() >= 368 && this->getPositionX() <= 440)
			height = 115;
		else
			height = 0;
		//上炮
		{
			
			if (heroInfo->m_speedUp <= 0 && this->getPositionY() < 230 && heroInfo->m_act != ONCANNON)
			{
				Rect cannonRect = { 230, 180, 40, 40 };
				if (cannonRect.containsPoint(this->getPosition()))
				{
					this->setPosition(250, 200);
					heroInfo->m_act = ONCANNON;
					return;
				}
			}
		}
		//落地
		if (this->getPositionY() <= height && heroInfo->m_speedUp <= 0)
		{
			this->setPositionY(height);
			heroInfo->m_speedUp = 0;
			heroInfo->m_act = MOVE;
		}
	}
	if (GameInfo::getInstance()->m_inBattleNum == 2)
	{
		if (this->getPositionY() <= 80 && heroInfo->m_speedUp <= 0)
		{
			this->setPositionY(80);
			heroInfo->m_speedUp = 0;
			heroInfo->m_act = MOVE;
		}
	}
}

void Hero::hit()   //可以加上枪支开火动画效果
{
	auto randNum = rand() * 10 % 2 + 1;
	auto heroInfo = HeroInfo::getInstance();
	int toward;
	{
		if (HeroInfo::getInstance()->m_towardX == LEFT)
		{
			toward = 3;
			if (heroInfo->m_gun == SMALL)
				m_launcher->setPosition(Vec2(-25, 18));
			else
				m_launcher->setPosition(Vec2(-25, 10));
		}
		else
		{
			toward = 1;
			if (heroInfo->m_gun == SMALL)
				m_launcher->setPosition(Vec2(-25, 18));
			else
				m_launcher->setPosition(Vec2(-25, 10));
		}
		if (HeroInfo::getInstance()->m_towardY == UP)
		{
			toward = 0;
			m_launcher->setPosition(Vec2(0, 40));
		}
		if (HeroInfo::getInstance()->m_towardY == DOWN)
		{
			if (HeroInfo::getInstance()->m_act == JUMP)
			{
				toward = 2;
			}
			if (heroInfo->m_gun == SMALL)
				m_launcher->setPosition(Vec2(-15, 13));
			else
				m_launcher->setPosition(Vec2(-15, 5));
		}
	}
	{
		if (heroInfo->m_act == STAND)
		{
			if (heroInfo->m_potHit)
			{
				//如果近战
				switch (heroInfo->m_towardY)
				{
				case DOWN:
				{
					auto fileName = StringUtils::format("squat_stop_pot%d", randNum);
					m_armature->getAnimation()->play(fileName);
				}
					break;
				default:
				{
					auto fileName = StringUtils::format("stand_stop_pot%d", randNum);
					m_armature->getAnimation()->play(fileName);
				}
					break;
				}
			}
			else
			{
				if (heroInfo->m_gun == SMALL)
				{
					//如果手枪
					switch (heroInfo->m_towardY)
					{
					case NORMAL:
						m_armature->getAnimation()->play("stand_stop_shoot_handgun_LR");
						break;
					case UP:
						m_armature->getAnimation()->play("stand_stop_shoot_handgun_UP");
						break;
					case DOWN:
						m_armature->getAnimation()->play("squat_stop_shoot_handgun_LR");
						break;
					default:
						break;
					}
				}
				else
				{
					//如果机关枪
					switch (heroInfo->m_towardY)
					{
					case NORMAL:
						m_armature->getAnimation()->play("stand_stop_shoot_rushgun_LR");
						break;
					case UP:
						m_armature->getAnimation()->play("stand_stop_shoot_rushgun_UP");
						break;
					case DOWN:
						m_armature->getAnimation()->play("squat_stop_shoot_rushgun_LR");
						break;
					default:
						break;
					}
				}
			}
		}
		else if (heroInfo->m_act == MOVE)
		{
			if (heroInfo->m_potHit)
			{
				//如果近战
				switch (heroInfo->m_towardY)
				{
				case DOWN:
				{
					auto fileName = StringUtils::format("squat_move_pot%d", randNum);
					m_armature->getAnimation()->play(fileName);
				}
					break;
				default:
				{
					auto fileName = StringUtils::format("stand_move_pot%d", randNum);
					m_armature->getAnimation()->play(fileName);
				}
					break;
				}
			}
			else
			{
				if (heroInfo->m_gun == SMALL)
				{
					//如果手枪
					switch (heroInfo->m_towardY)
					{
					case NORMAL:
						m_armature->getAnimation()->play("stand_move_shoot_handgun_LR");
						break;
					case UP:
						m_armature->getAnimation()->play("stand_move_shoot_handgun_UP");
						break;
					case DOWN:
						m_armature->getAnimation()->play("squat_move_shoot_handgun_LR");
						break;
					default:
						break;
					}
				}
				else
				{
					//如果机关枪
					switch (heroInfo->m_towardY)
					{
					case NORMAL:
						m_armature->getAnimation()->play("stand_move_shoot_rushgun_LR");
						break;
					case UP:
						m_armature->getAnimation()->play("stand_move_shoot_rushgun_UP");
						break;
					case DOWN:
						m_armature->getAnimation()->play("squat_move_shoot_rushgun_LR");
						break;
					default:
						break;
					}
				}
			}
		}
		else if (heroInfo->m_act == JUMP)
		{
			if (heroInfo->m_potHit)
			{
				//如果近战
				auto fileName = StringUtils::format("jump_pot%d", randNum);
				m_armature->getAnimation()->play(fileName);
			}
			else
			{
				if (heroInfo->m_gun == SMALL)
				{
					//如果手枪
					switch (heroInfo->m_towardY)
					{
					case UP:
						m_armature->getAnimation()->play("jump_normal_shoot_handgun_UP");
						break;
					default:
						m_armature->getAnimation()->play("jump_normal_shoot_handgun_LR");
						break;
					}
				}
				else
				{
					//如果机关枪
					switch (heroInfo->m_towardY)
					{
					case UP:
						m_armature->getAnimation()->play("jump_normal_shoot_rushgun_UP");
						break;
					default:
						m_armature->getAnimation()->play("jump_normal_shoot_rushgun_LR");
						break;
					}
				}
			}
		}
	}
	m_launcher->shoot(toward);
}

void Hero::throwBomb()
{
	auto heroInfo = HeroInfo::getInstance();
	switch (heroInfo->m_act)
	{
	case STAND:
		if (heroInfo->m_towardY == DOWN)
		{
			if (heroInfo->m_gun == SMALL)
			{
				m_armature->getAnimation()->play("squat_stop_handgun_throw");
			}
			else
			{
				m_armature->getAnimation()->play("squat_stop_rushgun_throw");
			}
		}
		else
		{
			if (heroInfo->m_gun == SMALL)
			{
				m_armature->getAnimation()->play("stand_stop_handgun_throw");
			}
			else
			{
				m_armature->getAnimation()->play("stand_stop_rushgun_throw");
			}
		}
		break;
	case MOVE:
		if (heroInfo->m_towardY == DOWN)
		{
			if (heroInfo->m_gun == SMALL)
			{
				m_armature->getAnimation()->play("squat_move_handgun_throw");
			}
			else
			{
				m_armature->getAnimation()->play("squat_move_rushgun_throw");
			}
		}
		else
		{
			if (heroInfo->m_gun == SMALL)
			{
				m_armature->getAnimation()->play("stand_move_handgun_throw");
			}
			else
			{
				m_armature->getAnimation()->play("stand_move_rushgun_throw");
			}
		}
		break;
	case JUMP:
		if (heroInfo->m_gun == SMALL)
		{
			m_armature->getAnimation()->play("jump_normal_handgun_throw");
		}
		else
		{
			m_armature->getAnimation()->play("jump_normal_rushgun_throw");
		}
		break;
	default:
		break;
	}
	//创建手雷逻辑
	auto bomb = Bomb::create();
	auto posInLayer = GameInfo::getInstance()->battleScene->convertToWorldSpace(this->getPosition());
	bomb->setPosition(posInLayer + Vec2(20,55));
	bomb->setBombData(15);
	GameInfo::getInstance()->battleScene->addChild(bomb);
	GameInfo::getInstance()->vHeroBomb.pushBack(bomb);
}

void Hero::armatureCallback(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	auto heroInfo = HeroInfo::getInstance();
	if (movementType == MovementEventType::LOOP_COMPLETE && heroInfo->m_isHitting)
	{
		heroInfo->m_isHitting = 0;
		heroInfo->m_potHit = 0;
	}
	if (movementType == MovementEventType::LOOP_COMPLETE && heroInfo->m_isThrowing)
	{
		heroInfo->m_isThrowing = 0;
	}
}

void Hero::updateCannon(bool left)
{
	if (left)
	{
		--m_toward;
		if (m_toward < -8)
			m_toward = -8;
	}
	else
	{
		++m_toward;
		if (m_toward > 8)
			m_toward = 8;
	}

	if (m_toward < 0)
		this->setScaleX(1);
	else
		this->setScaleX(-1);
	auto fileName = StringUtils::format("onCanon/image%d.png", 2040 + (int)(sqrt(m_toward*m_toward)) * 2);
	m_sprite->initWithFile(fileName);
	this->setPosition(Vec2(9 * -m_toward, 4 * (int)(sqrt(m_toward*m_toward))) + Vec2(250, 200));
}

void Hero::resetCannon()
{
	m_toward = 0;
	m_sprite->initWithFile("onCanon/image2040.png");
}

void Hero::escapeFromTruck()
{
	unscheduleUpdate();
	if (this->getPositionX() >= 110 && this->getPositionX() < 368)
	{
		this->setScaleX(1);
		auto X = this->getPositionX() - 110;
		auto time = X / 180;
		m_armature->getAnimation()->play("stand_move_handgun_LR");
		auto jumpCallback = CallFunc::create([this]()->void{m_armature->getAnimation()->play("jump_normal_handgun_LR"); });
		this->runAction(Sequence::create(DelayTime::create(0.2),
			MoveTo::create(time, Vec2(110, this->getPositionY())),
			Spawn::createWithTwoActions(jumpCallback, JumpBy::create(1, Vec2(-100, -200), 100, 1)), 
			nullptr));
	}
	else if (this->getPositionX() >= 368 && this->getPositionX() <= 440)
	{
		this->setScaleX(-1);
		auto X = 440 - this->getPositionX();
		auto time = X / 180;
		m_armature->getAnimation()->play("stand_move_handgun_LR");
		auto jumpCallback = CallFunc::create([this]()->void{m_armature->getAnimation()->play("jump_normal_handgun_LR"); });
		this->runAction(Sequence::create(DelayTime::create(0.2), 
			MoveTo::create(time, Vec2(440, this->getPositionY())),
			Spawn::createWithTwoActions(jumpCallback, JumpBy::create(1, Vec2(100, -200), 100, 1)),
			nullptr));
	}
}

void Hero::getIntoTruck()
{
	unscheduleUpdate();
	auto moveCallback = CallFunc::create([this]()->void {
		m_armature->getAnimation()->play("stand_move_handgun_LR");
		this->runAction(MoveBy::create(1, Vec2(200, 0)));
	});
	auto jumpCallback1 = CallFunc::create([this]()->void {
		m_armature->getAnimation()->play("jump_normal_handgun_LR");
		this->runAction(JumpBy::create(0.5, Vec2(0, 65), 85, 1));
	});
	auto jumpCallback2 = CallFunc::create([this]()->void {
		m_armature->getAnimation()->play("jump_normal_handgun_LR");
		this->runAction(JumpBy::create(0.5, Vec2(0, 100), 85, 1));
	});
	auto standCallback = CallFunc::create([this]()->void {
		m_armature->getAnimation()->play("stand_stop_handgun_LR");
	});
	this->runAction(Sequence::create(moveCallback, DelayTime::create(1), jumpCallback1, DelayTime::create(0.5), jumpCallback2, DelayTime::create(0.5), standCallback, nullptr));
}

void Hero::getIntoHeroPlane()
{
	unscheduleUpdate();
	m_armature->getAnimation()->play("jump_normal_handgun_LR");
}