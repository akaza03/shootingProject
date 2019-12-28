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
#include "Unit/Player.h"
#include "Unit/Enemy.h"

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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("GameMain", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

	//	レイヤーの作成
	BGLayer = Layer::create();
	this->addChild(BGLayer, LayerNumber::BG, "BGLayer");
	PLLayer = Layer::create();
	this->addChild(PLLayer, LayerNumber::PL, "PLLayer");
	EMLayer = Layer::create();
	this->addChild(EMLayer, LayerNumber::EM, "EMLayer");
	FGLayer = Layer::create();
	this->addChild(FGLayer, LayerNumber::FG, "FGLayer");
	UILayer = Layer::create();
	this->addChild(UILayer, LayerNumber::UI, "UILayer");

	//	マップの読み込み
	//TMXTiledMap* tiledMap = TMXTiledMap::create("map.tmx");
	//BGLayer->addChild(tiledMap, 1, "stageMap");

	//	Androidでエラー出るのでテスト用
	//	おそらく画像のパスか何かが悪い
	//	ゴミ
	auto spo = cocos2d::Sprite::create("image/player/00-unit.png");
	spo->setPosition(100, 100);
	BGLayer->addChild(spo, 0);

//	//	背景画像をまとめて表示する用
//	auto spNode = SpriteBatchNode::create(RES_ID("BackG01"));
//	BGLayer->addChild(spNode, 0);
//	for (int i = 0; i <= 2; i++)
//	{
//		auto BGSP = Sprite::createWithTexture(spNode->getTexture());
//		//	アンカーポイントを真ん中から左下に変更
//		BGSP->setAnchorPoint(Vec2(0, 0));
//		BGSP->setPosition(Vec2(BGSP->getContentSize().width * i, 0));
//		spNode->addChild(BGSP);
//	}
//
//	//	プレイヤーの作成
//	auto player = Player::create();
//
//	//	playerLayerを読み込み、プレイヤーの座標を決定する
//	TMXLayer* layer = tiledMap->getLayer("player");
//	//	プレイヤーの座標
//	cocos2d::Vec2 Ppos = cocos2d::Vec2(0, 0);
//	for (int y = 0; y < layer->getLayerSize().height; y++)
//	{
//		for (int x = 0; x < layer->getLayerSize().width; x++)
//		{
//			if (layer->getTileGIDAt(cocos2d::Vec2(x, y)) != 0)
//			{
//				Ppos = cocos2d::Vec2(x * layer->getMapTileSize().width,
//					layer->getLayerSize().height * layer->getMapTileSize().height - y * layer->getMapTileSize().height);
//				layer->removeFromParentAndCleanup(true);
//			}
//		}
//	}
//	player->SetInit(DIR::RIGHT, 0, Ppos, Vec2(5, 4), this);
//	PLLayer->addChild(player, 0);
//
//	//	敵の作成
//	TMXLayer* eLayer = tiledMap->getLayer("enemy");
//	//	エネミーの座標
//	cocos2d::Vec2 Epos;
//	for (int y = 0; y < eLayer->getLayerSize().height; y++)
//	{
//		for (int x = 0; x < eLayer->getLayerSize().width; x++)
//		{
//			if (eLayer->getTileGIDAt(cocos2d::Vec2(x, y)) != 0)
//			{
//				Epos = cocos2d::Vec2(x * eLayer->getMapTileSize().width, 
//					eLayer->getLayerSize().height * eLayer->getMapTileSize().height - y * eLayer->getMapTileSize().height);
//				auto Enemy = Enemy::create();
//				Enemy->SetInit(DIR::RIGHT, 0, Epos, Vec2(2, 4), this);
//				EMLayer->addChild(Enemy, 0);
//			}
//		}
//	}
//	eLayer->removeFromParentAndCleanup(true);
//
////#ifdef _DEBUG
////	//	デバッグ用レイヤーの作成
////	DBLayer = Layer::create();
////	this->addChild(DBLayer, LayerNumber::DB, "DBLayer");
////
////	//	デバッグ用Boxを作ってプレイヤーに渡す
////	auto DBBox = Sprite::create();
////	//DBBox->setColor(Color3B(0, 255, 128));
////	DBBox->setOpacity(128);
////	DBLayer->addChild(DBBox, 1, "DBBox");
////	player->SetDBBox(DBBox);
////#endif // _DEBUG
//
//	//	カメラ設定
//	auto size = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize();
//	BGLayer->runAction(Follow::create(player, Rect(0, 0, size.width*2.5, size.height)));
//	PLLayer->runAction(Follow::create(player, Rect(0, 0, size.width*2.5, size.height)));
//	EMLayer->runAction(Follow::create(player, Rect(0, 0, size.width*2.5, size.height)));
//	FGLayer->runAction(Follow::create(player, Rect(0, 0, size.width*2.5, size.height)));
//
//	//	BGMの設定
//	lpAudioManager.SetStream("music.cks", SoundType::S_BGM);

	this->scheduleUpdate();

	return true;
}

void GameScene::update(float d)
{
	//	エフェクトの更新
	lpEffectManager.update();

	//	Audioの更新
	lpAudioManager.update();
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}


