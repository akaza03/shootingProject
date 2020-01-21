#include "Character.h"
#include "Shot.h"

Shot::Shot()
{
}

Shot::~Shot()
{
}

void Shot::SetInit(std::string ImagePass, cocos2d::Sprite & sp, ActData &chara, float sPower, float sSpeed)
{
	hitChara = false;
	hitObj = false;
	auto charaPos = sp.getPosition();

	setPosition(charaPos);
	//	方向によって座標や向かう方向の変更
	if (chara.dir == DIR::LEFT)
	{
		setPosition(cocos2d::Vec2(charaPos.x - sp.getContentSize().width / 2, charaPos.y));
		speed = -sSpeed;
	}
	else if (chara.dir == DIR::RIGHT)
	{
		setPosition(cocos2d::Vec2(charaPos.x + sp.getContentSize().width / 2, charaPos.y));
		speed = sSpeed;
	}

	power = sPower;

	//	Shotに画像の追加
	this->addChild(Sprite::create(ImagePass),0,"shot");

	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();

	auto layer = nowScene->getChildByName("ATKLayer");

	type = chara.cType;
	charaID = chara.charaID;
	atkFlag = true;

	TypeInit(chara);

	this->setCameraMask(static_cast<int>(cocos2d::CameraFlag::USER1), true);
	
	layer->addChild(this,0);

	this->scheduleUpdate();
}

void Shot::update(float d)
{
	this->setPosition(getPosition().x + speed, getPosition().y);
	distance += speed;

	auto winSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	TypeUpdate();

	if (hitObj || hitChara || distance >= winSize.width / 2)
	{
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		auto layer = nowScene->getChildByName("ATKLayer");
		layer->removeChild(this);
	}
	else
	{
		HitCheck();
	}
}

CharaType Shot::GetType()
{
	return type;
}

float Shot::GetPower()
{
	return power;
}

bool Shot::GetAtkFlag()
{
	return atkFlag;
}

void Shot::SetHitChara(bool flag)
{
	hitChara = flag;
}

void Shot::TypeInit(ActData & chara)
{
	//	プレイヤー3(壁に当たるまで判定が発生しない)
	if (type == CharaType::PLAYER && charaID == 2)
	{
		this->getChildByName("shot")->setOpacity(100);
		atkFlag = false;
	}
}

void Shot::TypeUpdate()
{
	//	プレイヤー3
	if (type == CharaType::PLAYER && charaID == 2)
	{


		if (hitObj)
		{
			distance += 10;
			if (!atkFlag)
			{
				atkFlag = true;
				this->getChildByName("shot")->setOpacity(255);
			}
		}
		hitObj = false;
	}
}

void Shot::HitCheck()
{
	//	敵の弾との判定
	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
	auto layer = nowScene->getChildByName("ATKLayer");

	auto charaBox = cocos2d::Rect(this->getPosition(), this->getChildByName("shot")->getContentSize()/2);

	hitChara = false;

	for (auto obj : layer->getChildren())
	{
		auto objBox = obj->boundingBox();

		Shot* shot = (Shot*)obj;
		if ((shot->GetType() == CharaType::PLAYER && type == CharaType::ENEMY)
			|| (shot->GetType() == CharaType::ENEMY && type == CharaType::PLAYER))
		{
			if (charaBox.intersectsRect(objBox) && shot->GetAtkFlag())
			{
 				shot->SetHitChara(true);
				hitChara = true;
			}
		}
	}

	////	キャラクターとの判定
	//if (!hitChara)
	//{
	//	layer = nowScene->getChildByName("EMLayer");
	//	if (type == CharaType::ENEMY)
	//	{
	//		layer = nowScene->getChildByName("PLLayer");
	//	}
	//	for (auto obj : layer->getChildren())
	//	{
	//		//	判定用BOX
	//		auto objBox = obj->boundingBox();

	//		if (charaBox.intersectsRect(objBox))
	//		{
	//			//	当たった場合はダメージ硬直
	//			hitChara = true;
	//		}
	//		else
	//		{
	//			hitChara = false;
	//		}
	//	}
	//}


	//	障害物との判定

	//	衝突用のレイヤーの取得
	auto director = cocos2d::Director::getInstance();
	auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BGLayer")->getChildByName("stageMap");
	auto layerMap = map->getLayer("collision");

	//	弾の座標
	auto pos = cocos2d::Vec2(getPosition().x, layerMap->getLayerSize().height * layerMap->getMapTileSize().height - getPosition().y);
	//	指定された場所のタイルID
	int tile = 0;

	//	マップとの当たり判定
	auto colPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width, (pos.y + getContentSize().height / 2) / layerMap->getMapTileSize().height);

	if (colPos.x > 0 && colPos.x < layerMap->getLayerSize().width
		&&	colPos.y > 0 && colPos.y < layerMap->getLayerSize().height)
	{
		//	タイルの取得
		tile = layerMap->getTileGIDAt(colPos);
	}

	if (tile != 0)
	{
		hitObj =  true;
	}
	else
	{
		hitObj = false;
	}
}

