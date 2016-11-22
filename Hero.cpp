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
	default:
		break;
	}
	if (heroInfo->m_towardX_state == 2)
	{
		this->setPositionX(this->getPositionX() - heroInfo->m_speed);
		this->setScaleX(1);
	}
	if (heroInfo->m_towardX_state == 1)
	{
		this->setPositionX(this->getPositionX() + heroInfo->m_speed);
		this->setScaleX(-1);
	}
}

void Hero::jump()
{
	auto heroInfo = HeroInfo::getInstance();
	//for (int i = 0; i < ((BattleScene*)SceneManager::getInstance()->getBattleScene())->getRects().size(); ++i)
	//{
	//	//判断地图障碍物
	//	if (0/*遍历到障碍物*/)
	//	{
	//		
	//		return;
	//	}
	//}
	this->setPositionY(this->getPositionY() + heroInfo->m_speedUp);
	--heroInfo->m_speedUp;
	if (this->getPositionY() <= heroInfo->m_jumpStartY)  //调整下落位置
	{
		heroInfo->m_speedUp = 0;
		heroInfo->m_act = MOVE;
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
			m_launcher->setPosition(Vec2(-15, 30));
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
	auto posInLayer = BattleManager::getInstance()->battleScene->convertToWorldSpace(this->getPosition());
	bomb->setPosition(posInLayer + Vec2(20,35));
	bomb->setBombData(10);
	BattleManager::getInstance()->battleScene->addChild(bomb);
	BattleManager::getInstance()->vBomb.pushBack(bomb);
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