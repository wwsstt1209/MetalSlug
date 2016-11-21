#include "Launcher.h"

Launcher* Launcher::create()
{
	Launcher * ret = new (std::nothrow) Launcher();
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

bool Launcher::init()
{
	if (!Node::init())
	{
		return 0;
	}

	return 1;
}

void Launcher::initData(int gunType)
{
	m_level = gunType;
}

void Launcher::shoot(int toward)
{
	auto posLauncherInWorld = convertToWorldSpace(this->getPosition());
	switch (m_level)
	{
	case 0:    //手枪
	{
		auto b = Bullet::create();
		b->setPosition(posLauncherInWorld);
		b->initData(1, 10, toward);
		BattleManager::getInstance()->battleScene->addChild(b);
		BattleManager::getInstance()->vBullet.pushBack(b);
	} 
		break;
	case 1:    //机关枪
	{
		auto createBullet1 = CallFunc::create([this, posLauncherInWorld, toward]()->void{
			auto b = Bullet::create();
			if (HeroInfo::getInstance()->m_towardY == UP)
				b->setPosition(posLauncherInWorld + Vec2(2, 0));
			else
				b->setPosition(posLauncherInWorld + Vec2(0, 2));
			b->initData(1, 10, toward);
			BattleManager::getInstance()->battleScene->addChild(b);
			BattleManager::getInstance()->vBullet.pushBack(b);
		});
		auto createBullet2 = CallFunc::create([this, posLauncherInWorld, toward]()->void{
			auto b = Bullet::create();
			if (HeroInfo::getInstance()->m_towardY == UP)
				b->setPosition(posLauncherInWorld + Vec2(-2, 0));
			else
				b->setPosition(posLauncherInWorld + Vec2(0, -2));
			b->initData(1, 10, toward);
			BattleManager::getInstance()->battleScene->addChild(b);
			BattleManager::getInstance()->vBullet.pushBack(b);
		});
		auto createBullet3 = CallFunc::create([this, posLauncherInWorld, toward]()->void{
			auto b = Bullet::create();
			if (HeroInfo::getInstance()->m_towardY == UP)
				b->setPosition(posLauncherInWorld + Vec2(2, 0));
			else
				b->setPosition(posLauncherInWorld + Vec2(0, 2));
			b->initData(1, 10, toward);
			BattleManager::getInstance()->battleScene->addChild(b);
			BattleManager::getInstance()->vBullet.pushBack(b);
		});
		this->runAction(Sequence::create(createBullet1, DelayTime::create(0.1), createBullet2, DelayTime::create(0.1), createBullet3, nullptr));
	}
		break;
	case 2:    //导弹
		break;
	default:
		break;
	}
}