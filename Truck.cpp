#include "Truck.h"

Truck* Truck::create()
{
	Truck* ret = new(std::nothrow) Truck();
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

bool Truck::init()
{
	if (!Node::init())
	{
		return 0;
	}

	ArmatureDataManager::getInstance()->addArmatureFileInfo("Animations/TruckAnimation/TruckAnimation.ExportJson");
	m_armature = Armature::create("TruckAnimation");
	m_armature->getAnimation()->play("TruckStop");
	m_armature->setPosition(this->getContentSize() / 2);
	this->addChild(m_armature);

	m_cannon = Cannon::create();
	m_cannon->setPosition(Vec2(20, 100));
	this->addChild(m_cannon);
	Battle1Manager::getInstance()->m_Cannon = this->m_cannon;

	if (GameInfo::getInstance()->m_inBattleNum == 0)
	{
		auto moveCallback = CallFunc::create([this]()->void{
			m_armature->getAnimation()->play("TruckMoving");
			this->runAction(MoveBy::create(3, Vec2(500, 0)));
			GameInfo::getInstance()->m_hero->runAction(MoveBy::create(3, Vec2(500, 0)));
		});
		this->runAction(Sequence::create(DelayTime::create(2), moveCallback, nullptr));
	}

	if (GameInfo::getInstance()->m_inBattleNum == 1)
	{
		m_armature->getAnimation()->play("TruckMoving");
	}

	return 1;
}

void Truck::updateCannon(bool left)
{
	m_cannon->updateCannon(left);
}

void Truck::resetCannon()
{
	m_cannon->resetCannon();
}

void Truck::cannonFire(bool b)
{
	m_cannon->fire(b);
}