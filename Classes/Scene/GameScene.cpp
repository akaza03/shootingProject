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

	//	�X�N���[���T�C�Y�Ȃǂ̎擾
	screenSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	scSize = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize();

	//	���C���[�̍쐬
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

	//	�}�b�v�̓ǂݍ���
	TMXTiledMap* tiledMap = TMXTiledMap::create("map.tmx");
	BGLayer->addChild(tiledMap, 1, "stageMap");

	//	�}�b�v�T�C�Y
	auto mapSize = tiledMap->getContentSize();

	//	�w�i�摜���܂Ƃ߂ĕ\������p
	auto spNode = SpriteBatchNode::create(RES_ID("BackG01"));
	BGLayer->addChild(spNode, 0);
	for (int i = 0; i <= 5; i++)
	{
		auto BGSP = Sprite::createWithTexture(spNode->getTexture());
		//	�A���J�[�|�C���g��^�񒆂��獶���ɕύX
		BGSP->setAnchorPoint(Vec2(0, 0));
		BGSP->setPosition(Vec2(BGSP->getContentSize().width * i, 0));
		spNode->addChild(BGSP);
	}

	//	�v���C���[�̍쐬
	auto player = Player::create();

	//	playerLayer��ǂݍ��݁A�v���C���[�̍��W�����肷��
	TMXLayer* layer = tiledMap->getLayer("player");
	//	�v���C���[�̍��W
	cocos2d::Vec2 Ppos = cocos2d::Vec2(0, 0);
	for (int y = 0; y < layer->getLayerSize().height; y++)
	{
		for (int x = 0; x < layer->getLayerSize().width; x++)
		{
			if (layer->getTileGIDAt(cocos2d::Vec2(x, y)) != 0)
			{
				Ppos = cocos2d::Vec2(x * layer->getMapTileSize().width,
					layer->getLayerSize().height * layer->getMapTileSize().height - y * layer->getMapTileSize().height);
				layer->removeFromParentAndCleanup(true);
			}
		}
	}
	player->SetInit(DIR::RIGHT, 0, Ppos, 100, Vec2(5, 6), this);
	PLLayer->addChild(player, 0, "player");

	//	�G�̍쐬
	TMXLayer* eLayer = tiledMap->getLayer("enemy");
	enemyCnt = 0;
	//	�G�l�~�[�̍��W
	cocos2d::Vec2 Epos;
	for (int y = 0; y < eLayer->getLayerSize().height; y++)
	{
		for (int x = 0; x < eLayer->getLayerSize().width; x++)
		{
			if (eLayer->getTileGIDAt(cocos2d::Vec2(x, y)) != 0)
			{
				Epos = cocos2d::Vec2(x * eLayer->getMapTileSize().width, 
					eLayer->getLayerSize().height * eLayer->getMapTileSize().height - y * eLayer->getMapTileSize().height);
				auto Enemy = Enemy::create();
				Enemy->SetInit(DIR::RIGHT, 0, Epos, 10, Vec2(2, 4), this);
				EMLayer->addChild(Enemy, 0);
			}
		}
	}
	eLayer->removeFromParentAndCleanup(true);
	enemyCnt = EMLayer->getChildrenCount();

//#ifdef _DEBUG
//	//	�f�o�b�O�p���C���[�̍쐬
//	DBLayer = Layer::create();
//	this->addChild(DBLayer, LayerNumber::DB, "DBLayer");
//
//	//	�f�o�b�O�pBox������ăv���C���[�ɓn��
//	auto DBBox = Sprite::create();
//	//DBBox->setColor(Color3B(0, 255, 128));
//	DBBox->setOpacity(128);
//	DBLayer->addChild(DBBox, 1, "DBBox");
//	player->SetDBBox(DBBox);
//#endif // _DEBUG

	//	UI�쐬
	//	�v���C���[�̃A�C�R��
	auto uiSP = Sprite::create(RES_ID("p0icon"));
	uiSP->setPosition(uiSP->getContentSize().width / 1.5, screenSize.height - uiSP->getContentSize().height / 2);
	UILayer->addChild(uiSP, 1, "p0Icon");

	uiSP = Sprite::create(RES_ID("p1icon"));
	uiSP->setScale(0.6);
	uiSP->setPosition(uiSP->getContentSize().width / 1.5 + (uiSP->getContentSize().width / 2 * uiSP->getScaleX()), screenSize.height - uiSP->getContentSize().height - (uiSP->getContentSize().height / 2 * uiSP->getScaleY()));
	UILayer->addChild(uiSP, 1, "p1Icon");

	uiSP = Sprite::create(RES_ID("p2icon"));
	uiSP->setScale(0.6);
	uiSP->setPosition(uiSP->getContentSize().width / 1.5 - (uiSP->getContentSize().width / 2 * uiSP->getScaleX()), screenSize.height - uiSP->getContentSize().height - (uiSP->getContentSize().height / 2 * uiSP->getScaleY()));
	UILayer->addChild(uiSP, 1, "p2Icon");


	//	�v���C���[��HP�o�[(��)
	auto hpBar = Sprite::create(RES_ID("HPBase"));
	hpBar->setPosition(hpBar->getContentSize().width, screenSize.height - hpBar->getContentSize().height);
	hpBar->setOpacity(150);
	UILayer->addChild(hpBar, 1, "hpBase");
	//	�v���C���[��HP�o�[
	hpBar = Sprite::create(RES_ID("HP"));
	hpBar->setPosition(hpBar->getContentSize().width, screenSize.height - hpBar->getContentSize().height);
	hpBar->setOpacity(200);
	UILayer->addChild(hpBar, 1, "hpBar");

	//auto score = String::createWithFormat("�c��F%i��", enemyCnt);
	//auto label = Label::createWithSystemFont(score->getCString(), "arial", 80);
	//label->setPosition(scSize.width / 2, scSize.height / 2);
	//UILayer->addChild(label, 1, "enemyCounter");

	//	�|�[�Y���ȂǗp�̍�����
	auto fadeImage = Sprite::create();
	fadeImage->setTextureRect(Rect(0, 0, scSize.width * 2, scSize.height * 2));
	fadeImage->setPosition(0, 0);
	fadeImage->setColor(Color3B(0, 0, 0));
	fadeImage->setOpacity(0);
	BWLayer->addChild(fadeImage,0,"fade");

	//	BGM�̐ݒ�
	//lpAudioManager.SetStream("music.cks", SoundType::S_BGM);

	//	�v���b�g�t�H�[���ɂ���đ�����@��ς���
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

	//	�J�����̃Z�b�g

	//BGLayer->runAction(Follow::create(player, Rect(0, 0, mapSize.width, screenSize.height)));
	//PLLayer->runAction(Follow::create(player, Rect(0, 0, mapSize.width, screenSize.height)));
	//EMLayer->runAction(Follow::create(player, Rect(0, 0, mapSize.width, screenSize.height)));
	//FGLayer->runAction(Follow::create(player, Rect(0, 0, mapSize.width, screenSize.height)));

	_camera = Camera::createOrthographic(screenSize.width, screenSize.height, 0, 1000);

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

	//	����C�x���g�̍쐬
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_oprtState->oprtInit(), this);

	this->scheduleUpdate();

	return true;
}

void GameScene::update(float d)
{
	//	�G�t�F�N�g�̍X�V
	lpEffectManager.update(_camera);
	//	Audio�̍X�V
	lpAudioManager.update();
	//	�V�X�e���L�[�̍X�V
	keyUpdate();
	//	camera�̍X�V
	cameraUpdate();
	//	�Q�[���̃N���A����
	screenUpdate();

	for (auto itrKey : UseKey())
	{
		key[itrKey].second = key[itrKey].first;
	}
}

void GameScene::cameraUpdate()
{
	auto playerPos = this->getChildByName("PLLayer")->getChildByName("player")->getPosition();
	//	�}�b�v�̃T�C�Y
	auto mapSize = BGLayer->getChildByName("stageMap")->getContentSize();

	//	�v���C���[����J�����̍��[�܂ł̋���
	auto leftDis = playerPos.x - screenSize.width / 2;
	//	�J�����̉E�[����v���C���[�܂ł̋���
	auto rightDis = mapSize.width - playerPos.x;

	//	���[����
	if (leftDis < 0)
	{
		_camera->setPosition3D(Vec3(0, 0, 0));
	}
	//	�E�[����
	else if (rightDis < screenSize.width / 2)
	{
		_camera->setPosition3D(Vec3(mapSize.width - screenSize.width, 0, 0));
	}
	//	�ʏ�̃X�N���[��
	else
	{
		_camera->setPosition3D(Vec3(playerPos.x - screenSize.width / 2, 0, 0));
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
	//	�Q�[���N���Aor�Q�[���I�[�o�[����
	if (EMLayer->getChildrenCount() == 0 || pl->CheckAnim() == AnimState::DIE)
	{
		if (!gameEndFlag)
		{
			BWLayer->getChildByName("fade")->setOpacity(120);
			//pause(PLLayer);
			pause(EMLayer);
			pause(ATKLayer);
			pause(BGLayer);
			pause(FGLayer);

			//	�Q�[���N���A
			if (EMLayer->getChildrenCount() == 0)
			{
				pause(PLLayer);
				CCLabelTTF *text = CCLabelTTF::create("GAME CLEAR!", "Arial", 80);
				if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
				{
					text->setPosition(scSize.width / 2, scSize.height / 2);
				}
				else
				{
					text->setPosition(scSize.width / 2, scSize.height / 4);
				}
				BWLayer->addChild(text);
			}
			//	�Q�[���I�[�o�[
			if (pl->CheckAnim() == AnimState::DIE)
			{
				CCLabelTTF *text = CCLabelTTF::create("GAME OVER", "Arial", 80);
				if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
				{
					text->setPosition(scSize.width / 2, scSize.height / 2);
				}
				else
				{
					text->setPosition(scSize.width / 2, scSize.height / 4);
				}
				BWLayer->addChild(text);
			}

			if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
			{
				CCLabelTTF *text = CCLabelTTF::create("PLEASE TO ENTER", "Arial", 30);
				text->setPosition(scSize.width / 2, scSize.height / 2 - 100);
				BWLayer->addChild(text);
			}
			else
			{
				CCLabelTTF *text = CCLabelTTF::create("PLEASE TO TAP", "Arial", 30);
				text->setPosition(scSize.width / 2, scSize.height / 4 - 100);
				BWLayer->addChild(text);
			}

			gameEndFlag = true;
		}

		//	Enter�ł�����x�v���C
		if (key[UseKey::K_ENTER].first && !key[UseKey::K_ENTER].second || _oprtState->firstTouch())
		{
			lpAudioManager.ResetAudio();
			auto scene = GameScene::createScene();
			// scene�̐���
			Director::getInstance()->replaceScene(scene);
		}
	}
	else
	{
		//	�|�[�Y���
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
		//	�|�[�Y����
		if (pauseFlag)
		{
			childs->resumeSchedulerAndActions();
		}
		//	�|�[�Y�J�n
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


