#include "Hostage.h"

Hostage* Hostage::create()
{
	Hostage * ret = new (std::nothrow) Hostage();
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

bool Hostage::init()
{
	if (!Node::init())
	{
		return 0;
	}
	scheduleUpdate();

	GameInfo::getInstance()->vEnemy.pushBack(this);

	ArmatureDataManager::getInstance()->addArmatureFileInfo("Animations/HostageAnimation/HostageAnimation.ExportJson");
	m_armature = Armature::create("HostageAnimation");
	m_armature->getAnimation()->play("wait");

	this->addChild(m_armature);

	return 1;
}

void Hostage::update(float dt)
{
	auto hero = GameInfo::getInstance()->m_hero;
	auto movementID = m_armature->getAnimation()->getCurrentMovementID();
	auto posInWorld = this->convertToWorldSpace(this->getPosition());
	auto posInScene = GameInfo::getInstance()->battleScene->convertToNodeSpace(posInWorld);
	auto posHeroInHostage = this->convertToNodeSpaceAR(hero->getPosition());
	if (fabs(posHeroInHostage.x) <= 250 && fabs(posHeroInHostage.x) >= 80 && movementID != "call")
		m_armature->getAnimation()->play("call");
	else if(fabs(posHeroInHostage.x) < 80 && movementID != "sawhero")
		m_armature->getAnimation()->play("sawhero");
	if (!Rect(0,0,560,400).containsPoint(posInWorld))
	{
		GameInfo::getInstance()->vEnemy.eraseObject(this);
		this->removeFromParent();
	}
}