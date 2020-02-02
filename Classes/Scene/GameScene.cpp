/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Input/OprtTouch.h"
#include "Map/MapMaker.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ///////////////////////////////
    //// 2. add a menu item with "X" image, which is clicked to quit the program
    ////    you may modify it.

    //// add a "close" icon to exit the progress. it's an autorelease object
    //auto closeItem = MenuItemImage::create(
    //                                       "CloseNormal.png",
    //                                       "CloseSelected.png",
    //                                       CC_CALLBACK_1(GameScene::menuCloseCallback, this));

    //if (closeItem == nullptr ||
    //    closeItem->getContentSize().width <= 0 ||
    //    closeItem->getContentSize().height <= 0)
    //{
    //    problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    //}
    //else
    //{
    //    float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
    //    float y = origin.y + closeItem->getContentSize().height/2;
    //    closeItem->setPosition(Vec2(x,y));
    //}

    //// create menu, it's an autorelease object
    //auto menu = Menu::create(closeItem, NULL);
    //menu->setPosition(Vec2::ZERO);
    //this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    //auto label = Label::createWithTTF("GameMain", "fonts/Marker Felt.ttf", 24);
    //if (label == nullptr)
    //{
    //    problemLoading("'fonts/Marker Felt.ttf'");
    //}
    //else
    //{
    //    // position the label on the center of the screen
    //    label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                            origin.y + visibleSize.height - label->getContentSize().height));

    //    // add the label as a child to this layer
    //    this->addChild(label, 1);
    //}

	//	スクリーンサイズなどの取得
	confScSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	scSize = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize();

	//	レイヤーの作成
	BGLayer = Layer::create();
	this->addChild(BGLayer, LayerNumber::BG, "BGLayer");
	PLLayer = Layer::create();
	this->addChild(PLLayer, LayerNumber::PL, "PLLayer");
	EMLayer = Layer::create();
	this->addChild(EMLayer, LayerNumber::EM, "EMLayer");
	ATKLayer = Layer::create();
	this->addChild(ATKLayer, LayerNumber::ATK, "ATKLayer");
	FGLayer = Layer::create();
	this->addChild(FGLayer, LayerNumber::FG, "FGLayer");
	UILayer = Layer::create();
	this->addChild(UILayer, LayerNumber::UI, "UILayer");
	BWLayer = Layer::create();
	this->addChild(BWLayer, LayerNumber::BW, "BWLayer");

	//	マップの読み込み
	auto map = MapMaker::create();

	map->SetMap("map.tmx", BGLayer, "stageMap");

	//	マップサイズ
	auto mapSize = map->GetMapSize();

	//	背景画像をまとめて表示する用
	map->SetBackImage(RES_ID("BackG01"),BGLayer);

	//	プレイヤーの作成
	map->SetChara(CharaType::PLAYER, PLLayer, this);
	//	敵の作成
	map->SetChara(CharaType::ENEMY, EMLayer, this);
	enemyCnt = EMLayer->getChildrenCount();

	//	UI作成
	SetUI();

	//	BGMの設定
	lpAudioManager.SetSound("music.cks");

	//	プラットフォームによって操作方法を変える
	if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
	{
		_oprtState = new OprtKey();
	}
	else
	{
		_oprtState = new OprtTouch();
	}
	pauseFlag = false;
	gameEndFlag = false;

	//	カメラのセット
	_camera = Camera::createOrthographic(confScSize.width, confScSize.height, 0, 1000);
	cameraUpdate();

	this->addChild(_camera);
	_camera->setCameraFlag(CameraFlag::USER1);

	BGLayer->setCameraMask(static_cast<int>(CameraFlag::USER1), true);
	PLLayer->setCameraMask(static_cast<int>(CameraFlag::USER1), true);
	EMLayer->setCameraMask(static_cast<int>(CameraFlag::USER1), true);
	ATKLayer->setCameraMask(static_cast<int>(CameraFlag::USER1), true);
	FGLayer->setCameraMask(static_cast<int>(CameraFlag::USER1), true);

	//UILayer->setCameraMask(static_cast<int>(CameraFlag::USER1), true);
	//BWLayer->setCameraMask(static_cast<int>(CameraFlag::USER1), true);

	//	操作イベントの作成
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_oprtState->oprtInit(), this);

	this->scheduleUpdate();

	return true;
}

void GameScene::SetUI()
{
	//	プレイヤーのアイコン
	auto uiSP = Sprite::create(RES_ID("p0icon"));
	uiSP->setPosition(uiSP->getContentSize().width / 1.5, confScSize.height - uiSP->getContentSize().height / 2);
	UILayer->addChild(uiSP, 1, "p0Icon");

	uiSP = Sprite::create(RES_ID("p1icon"));
	uiSP->setScale(0.6);
	uiSP->setPosition(uiSP->getContentSize().width / 1.5 + (uiSP->getContentSize().width / 2 * uiSP->getScaleX()), confScSize.height - uiSP->getContentSize().height - (uiSP->getContentSize().height / 2 * uiSP->getScaleY()));
	UILayer->addChild(uiSP, 1, "p1Icon");

	uiSP = Sprite::create(RES_ID("p2icon"));
	uiSP->setScale(0.6);
	uiSP->setPosition(uiSP->getContentSize().width / 1.5 - (uiSP->getContentSize().width / 2 * uiSP->getScaleX()), confScSize.height - uiSP->getContentSize().height - (uiSP->getContentSize().height / 2 * uiSP->getScaleY()));
	UILayer->addChild(uiSP, 1, "p2Icon");


	//	プレイヤーのHPバー(下)
	auto hpBar = Sprite::create(RES_ID("HPBase"));
	hpBar->setPosition(hpBar->getContentSize().width, confScSize.height - hpBar->getContentSize().height);
	hpBar->setOpacity(150);
	UILayer->addChild(hpBar, 1, "hpBase");
	//	プレイヤーのHPバー
	hpBar = Sprite::create(RES_ID("HP"));
	hpBar->setPosition(hpBar->getContentSize().width, confScSize.height - hpBar->getContentSize().height);
	hpBar->setOpacity(200);
	UILayer->addChild(hpBar, 1, "hpBar");

	//	敵の残り数
	auto remain = Sprite::create(RES_ID("ReMain"));
	remain->setPosition(confScSize.width - 180, confScSize.height - 40);
	UILayer->addChild(remain, 1, "remain");

	enemyCntInit();

	//	ポーズ時など用の黒い幕
	auto fadeImage = Sprite::create();
	fadeImage->setTextureRect(Rect(0, 0, scSize.width * 2, scSize.height * 2));
	fadeImage->setPosition(0, 0);
	fadeImage->setColor(Color3B(0, 0, 0));
	fadeImage->setOpacity(0);
	BWLayer->addChild(fadeImage, 0, "fade");
}

void GameScene::update(float d)
{
	//	敵の残り数表示更新
	enemyCnt = EMLayer->getChildrenCount();
	number->setNumber(enemyCnt);

	//	エフェクトの更新
	lpEffectManager.update(_camera);
	//	Audioの更新
	lpAudioManager.update();
	//	システムキーの更新
	keyUpdate();
	//	cameraの更新
	cameraUpdate();
	//	ゲームのクリア処理
	screenUpdate();



	for (auto itrKey : UseKey())
	{
		key[itrKey].second = key[itrKey].first;
	}
}

void GameScene::enemyCntInit()
{
	number = Number::create();
	number->setPosition(confScSize.width - 60, confScSize.height - 40);
	number->setSpan(40);
	number->setPrefix("number");
	UILayer->addChild(number, 1, "enemyCounter");
}

void GameScene::cameraUpdate()
{
	auto playerPos = this->getChildByName("PLLayer")->getChildByName("player")->getPosition();
	//	マップのサイズ
	auto mapSize = BGLayer->getChildByName("stageMap")->getContentSize();

	//	プレイヤーからカメラの左端までの距離
	auto leftDis = playerPos.x - confScSize.width / 2;
	//	カメラの右端からプレイヤーまでの距離
	auto rightDis = mapSize.width - playerPos.x;

	//	左端処理
	if (leftDis < 0)
	{
		_camera->setPosition3D(Vec3(0, 0, 0));
	}
	//	右端処理
	else if (rightDis < confScSize.width / 2)
	{
		_camera->setPosition3D(Vec3(mapSize.width - confScSize.width, 0, 0));
	}
	//	通常のスクロール
	else
	{
		_camera->setPosition3D(Vec3(playerPos.x - confScSize.width / 2, 0, 0));
	}
}

void GameScene::keyUpdate()
{
	for (auto checkKey : _oprtState->GetKeyList())
	{
		key[checkKey.first].first = checkKey.second;
	}
}

void GameScene::screenUpdate()
{
	Character* pl = (Character*)PLLayer->getChildByName("player");
	//	ゲームクリアorゲームオーバー処理
	if (enemyCnt == 0 || pl->CheckAnim() == AnimState::DIE)
	{
		if (!gameEndFlag)
		{
			BWLayer->getChildByName("fade")->setOpacity(120);
			pause(EMLayer);
			pause(ATKLayer);
			pause(BGLayer);
			pause(FGLayer);

			//	ゲームクリア
			if (enemyCnt == 0)
			{
				pause(PLLayer);
				CCLabelTTF *text = CCLabelTTF::create("GAME CLEAR!", "Arial", 80);
				if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
				{
					text->setPosition(confScSize.width / 2, confScSize.height / 2);
				}
				else
				{
					text->setPosition(confScSize.width / 2, confScSize.height / 2);
				}
				BWLayer->addChild(text);
			}
			//	ゲームオーバー
			if (pl->CheckAnim() == AnimState::DIE)
			{
				CCLabelTTF *text = CCLabelTTF::create("GAME OVER", "Arial", 80);
				if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
				{
					text->setPosition(confScSize.width / 2, confScSize.height / 2);
				}
				else
				{
					text->setPosition(confScSize.width / 2, confScSize.height / 2);
				}
				BWLayer->addChild(text);
			}

			if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
			{
				CCLabelTTF *text = CCLabelTTF::create("PLEASE TO ENTER", "Arial", 30);
				text->setPosition(confScSize.width / 2, confScSize.height / 2 - 100);
				BWLayer->addChild(text);
			}
			else
			{
				CCLabelTTF *text = CCLabelTTF::create("PLEASE TO TAP", "Arial", 30);
				text->setPosition(confScSize.width / 2, confScSize.height / 2 - 100);
				BWLayer->addChild(text);
			}

			gameEndFlag = true;
		}

		//	Enterでもう一度プレイ
		if (key[UseKey::K_ENTER].first && !key[UseKey::K_ENTER].second || _oprtState->firstTouch())
		{
			lpAudioManager.ResetAudio();
			lpAudioManager.SetSound("click");
			auto scene = GameScene::createScene();
			// sceneの生成
			Director::getInstance()->replaceScene(scene);
		}
	}
	else
	{
		//	ポーズ画面
		if (key[UseKey::K_ENTER].first && !key[UseKey::K_ENTER].second)
		{
			pause(PLLayer);
			pause(EMLayer);
			pause(ATKLayer);
			pause(BGLayer);
			pause(FGLayer);

			if (pauseFlag)
			{
				BWLayer->removeChildByName("pauseText");
				BWLayer->getChildByName("fade")->setOpacity(0);
				pauseFlag = false;
			}
			else
			{
				CCLabelTTF *text = CCLabelTTF::create("PAUSE", "Arial", 80);
				text->setPosition(scSize.width / 2, scSize.height / 2);
				BWLayer->addChild(text, 1, "pauseText");

				BWLayer->getChildByName("fade")->setOpacity(120);
				pauseFlag = true;
			}
		}
	}
}

void GameScene::pause(cocos2d::Layer * layer)
{
	auto scSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	for (auto* childs : layer->getChildren())
	{
		//	ポーズ解除
		if (pauseFlag)
		{
			childs->resumeSchedulerAndActions();
		}
		//	ポーズ開始
		else
		{
			childs->pauseSchedulerAndActions();
		}
	}
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}


