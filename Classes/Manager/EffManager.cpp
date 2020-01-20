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

void EffManager::update(cocos2d::Camera* camera)
{
	(*effectMng).update();
	//	カメラ関連の更新
	(*effectMng).setCameraMatrix(camera->getViewMatrix());
	(*effectMng).setProjectionMatrix(camera->getProjectionMatrix());
}

void EffManager::SetEffect(const char* pass, const char* layer, cocos2d::Vec2 pos, int scale, bool playEnter)
{
	auto effect = efk::Effect::create(pass);

	if (effect != nullptr)
	{
		auto emitter = efk::EffectEmitter::create(effectMng.get());
		emitter->setEffect(effect);
		emitter->setPlayOnEnter(true);
		emitter->setPosition(pos);
		emitter->setScale(scale);
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		auto nowLayer = nowScene->getChildByName(layer);

		emitter->setCameraMask(static_cast<int>(cocos2d::CameraFlag::USER1), true);
		nowLayer->addChild(emitter, 0);
	}
}
