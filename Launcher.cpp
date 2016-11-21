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
	case 0:    //��ǹ
	{
		auto b = Bullet::create();
		b->setPosition(posLauncherInWorld);

		b->initData(1, 10, toward);
		m_layer->addChild(b);
	}
		break;
	case 1:    //����ǹ
		break;
	case 2:    //����
		break;
	default:
		break;
	}
}