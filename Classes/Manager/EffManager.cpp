#include "EffManager.h"

EffManager* EffManager::s_Instance = nullptr;

EffManager::EffManager()
{
	effectMng.reset(efk::EffectManager::create(cocos2d::Director::getInstance()->getVisibleSize()));
}


EffManager::~EffManager()
{
	effectMng->release();
}

void EffManager::update()
{
	(*effectMng).update();
}

void EffManager::SetEffect(const char* pass, const char* layer, cocos2d::Vec2 pos, int scale, bool playEnter)
{
	auto effect = efk::Effect::create(pass);

	auto emitter = efk::EffectEmitter::create(effectMng.get());
	emitter->setEffect(effect);
	emitter->setPosition(pos);
	emitter->setScale(scale);
	emitter->setPlayOnEnter(playEnter);
	
	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
	auto nowLayer = nowScene->getChildByName(layer);
	nowLayer->addChild(emitter, 0);
}
