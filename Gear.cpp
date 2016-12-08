#include "Gear.h"

Gear* Gear::create(std::string& fileName)
{
	Gear* ret = new(std::nothrow) Gear();
	if (ret && ret->init(fileName))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool Gear::init(std::string& fileName)
{
	if (!Node::init())
	{
		return 0;
	}

	m_spr = Sprite::create(fileName);
	m_hp = 5;

	return 1;
}

Sprite* Gear::getSprite()
{
	return m_spr;
}

void Gear::hit()
{
	--m_hp;
	m_spr->runAction(Sequence::create(TintTo::create(0.05, 255, 0, 0), TintTo::create(0.05, 255,255,255), nullptr));
}

bool Gear::resetTexture()
{
	bool ret = 0;
	if (m_hp == 2)
		ret = 1;
	return ret;
}

bool Gear::tryToRemove()
{
	bool ret = 0;
	if (m_hp == 0)
	{
		auto explode = Sprite::create();
		GameInfo::getInstance()->battleScene->addChild(explode);
		explode->setPosition(m_spr->convertToWorldSpace(Vec2::ZERO) + m_spr->getContentSize() / 2);
		explode->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("GearExplode")),
			CallFunc::create([explode]()->void {explode->removeFromParent();}),
			nullptr));

		m_spr->removeFromParent();
		ret = 1;
	}
	return ret;
}