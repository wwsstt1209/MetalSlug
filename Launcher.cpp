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
	auto posLauncherInScene = BattleManager::getInstance()->battleScene->convertToNodeSpace(posLauncherInWorld);
	switch (m_level)
	{
	case 0:    //��ǹ
	{
		auto b = Bullet::create();
		b->setPosition(posLauncherInScene);
		b->initData(0, 10, toward);
		BattleManager::getInstance()->battleScene->addChild(b, 3);
	} 
		break;
	case 1:    //����ǹ
	{
		auto createBullet1 = CallFunc::create([this, posLauncherInScene, toward]()->void{
			auto b = Bullet::create();
			if (HeroInfo::getInstance()->m_towardY == UP)
				b->setPosition(posLauncherInScene + Vec2(2, 0));
			else
				b->setPosition(posLauncherInScene + Vec2(0, 2));
			b->initData(0, 10, toward);
			BattleManager::getInstance()->battleScene->addChild(b, 3);
		});
		auto createBullet2 = CallFunc::create([this, posLauncherInScene, toward]()->void{
			auto b = Bullet::create();
			if (HeroInfo::getInstance()->m_towardY == UP)
				b->setPosition(posLauncherInScene + Vec2(-2, 0));
			else
				b->setPosition(posLauncherInScene + Vec2(0, -2));
			b->initData(0, 10, toward);
			BattleManager::getInstance()->battleScene->addChild(b);
		});
		auto createBullet3 = CallFunc::create([this, posLauncherInScene, toward]()->void{
			auto b = Bullet::create();
			if (HeroInfo::getInstance()->m_towardY == UP)
				b->setPosition(posLauncherInScene + Vec2(2, 0));
			else
				b->setPosition(posLauncherInScene + Vec2(0, 2));
			b->initData(0, 10, toward);
			BattleManager::getInstance()->battleScene->addChild(b);
		});
		this->runAction(Sequence::create(createBullet1, DelayTime::create(0.1), createBullet2, DelayTime::create(0.1), createBullet3, nullptr));
	}
		break;
	case 2:    //����
		break;
	default:
		break;
	}
}

void Launcher::showShootEffect(int toward)
{

}