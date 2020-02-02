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

	auto scSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	auto BGSP = Sprite::create(RES_ID("Title"));
	BGSP->setAnchorPoint(Vec2(0, 0));
	BGSP->setPosition(Vec2(0, 0));
	this->addChild(BGSP);

	BGSP = Sprite::create(RES_ID("logo"));
	BGSP->setPosition(scSize / 2);
	this->addChild(BGSP);
	

	//CCLabelTTF *text = CCLabelTTF::create("MAGIA SHOT", "Arial", 150);
	//text->setPosition(scSize.width / 2, scSize.height / 2 + 50);
	//this->addChild(text);

	//	プラットフォームによって操作方法を変える
	if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
	{
		_oprtState = new OprtKey();
		CCLabelTTF *text = CCLabelTTF::create("PLEASE TO ENTER", "Arial", 50);
		text->setPosition(scSize.width / 2, scSize.height / 2 - 150);
		this->addChild(text);
	}
	else
	{
		_oprtState = new OprtTouch();
		CCLabelTTF *text = CCLabelTTF::create("PLEASE TO TAP", "Arial", 50);
		text->setPosition(scSize.width / 2, scSize.height / 2 - 150);
		this->addChild(text);
	}

	lpAudioManager.SetSound("titleBGM.cks");

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
	//	Audioの更新
	lpAudioManager.update();

	for (auto checkKey : _oprtState->GetKeyList())
	{
		key[checkKey.first].first = checkKey.second;
	}

	if (key[UseKey::K_ENTER].first && !key[UseKey::K_ENTER].second || _oprtState->firstTouch())
	{
		lpAudioManager.ResetAudio();
		lpAudioManager.SetSound("click");
		auto scene = GameScene::createScene();
		// sceneの生成
		Director::getInstance()->replaceScene(scene);
	}

	for (auto itrKey : UseKey())
	{
		key[itrKey].second = key[itrKey].first;
	}
}
