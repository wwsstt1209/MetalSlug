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
	m_armature->getAnimation()->play("Animation1");
	m_armature->setPosition(this->getContentSize() / 2);
	this->addChild(m_armature);

	return 1;
}