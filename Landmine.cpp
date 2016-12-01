#include "Landmine.h"

Landmine* Landmine::create()
{
	Landmine* ret = new(std::nothrow) Landmine();
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

bool Landmine::init()
{
	if (!Node::init())
	{
		return 0;
	}
	scheduleUpdate();
	schedule(CC_CALLBACK_1(Landmine::updateSprite, this), 0.1, "landmine");

	m_sprite = Sprite::create("landmine/image730.png");
	this->addChild(m_sprite);

	if (AnimationCache::getInstance()->getAnimation("landmineExplode") == nullptr)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("landmine/LandmineAnimation.plist");
		Vector<SpriteFrame*>vec;
		for (int i = 0; i < 13; ++i)
		{
			auto fileName = StringUtils::format("image%d.png", 734 + i * 2);
			vec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
		}
		auto ani = Animation::createWithSpriteFrames(vec);
		ani->setDelayPerUnit(0.1);
		AnimationCache::getInstance()->addAnimation(ani, "landmineExplode");
	}

	return 1;
}

void Landmine::update(float dt)
{
	auto hero = GameInfo::getInstance()->m_hero;
	auto posInHero = this->convertToNodeSpace(hero->getPosition());
	if (posInHero.y <= 10 && fabs(posInHero.x) <= 30)
	{
		scheduleOnce(CC_CALLBACK_0(Landmine::resetPos,this), 0.2, "resetpos");
		auto release = CallFunc::create([this]()->void{
			this->removeFromParent();
		});
		m_sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("landmineExplode")), 
			release,nullptr));
		unschedule("landmine");
		unscheduleUpdate();
	}
}

void Landmine::updateSprite(float dt)
{
	if (m_sprite->getResourceName() == "landmine/image730.png")
		m_sprite->initWithFile("landmine/image732.png");
	else
		m_sprite->initWithFile("landmine/image730.png");
}

void Landmine::explode()
{
	unschedule("landmine");
	unscheduleUpdate();

}

void Landmine::resetPos()
{
	this->setPositionY(this->getPositionY() + 40);
}