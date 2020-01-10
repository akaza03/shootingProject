#include "TitleScene.h"
#include "Input/OprtTouch.h"
#include "GameScene.h"

USING_NS_CC;

cocos2d::Scene * TitleScene::createScene()
{
	return TitleScene::create();
}

bool TitleScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//	プラットフォームによって操作方法を変える
	if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
	{
		_oprtState = new OprtKey();
	}
	else
	{
		_oprtState = new OprtTouch();
	}

	//	操作イベントの作成
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_oprtState->oprtInit(), this);

	this->scheduleUpdate();

	return true;
}

void TitleScene::menuCloseCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();
}

void TitleScene::update(float d)
{
	for (auto checkKey : _oprtState->GetKeyList())
	{
		key[checkKey.first].first = checkKey.second;
	}

	if (key[UseKey::K_ENTER].first && !key[UseKey::K_ENTER].second || _oprtState->firstTouch())
	{
		//lpAudioManager.ResetAudio();
		auto scene = GameScene::createScene();
		// sceneの生成
		Director::getInstance()->replaceScene(scene);
	}

	for (auto itrKey : UseKey())
	{
		key[itrKey].second = key[itrKey].first;
	}
}
