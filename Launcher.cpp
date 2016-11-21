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
	if (!Node::create())
	{
		return 0;
	}

	return 1;
}

void Launcher::initData(Layer* pLayer, int lvl)
{
	m_layer = pLayer;
	m_level = lvl;
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
		m_layer->addChild(b);
	}
		break;
	case 1:    //机关枪
		break;
	case 2:    //导弹
		break;
	default:
		break;
	}
}