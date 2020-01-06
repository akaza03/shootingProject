#include "Character.h"
#include "Shot.h"

Shot::Shot()
{
}

Shot::~Shot()
{
}

void Shot::SetInit(std::string ImagePass, cocos2d::Sprite & sp, ActData &chara, float sSpeed)
{
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

	//	Shotに画像の追加
	this->addChild(Sprite::create(ImagePass));

	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();

	//	撃ったキャラの種類によってレイヤー分け
	auto layer = nowScene->getChildByName("PLLayer");
	if (chara.cType == CharaType::ENEMY)
	{
		layer = nowScene->getChildByName("EMLayer");
	}

	type = chara.cType;
	
	layer->addChild(this,0);

	this->scheduleUpdate();
}

void Shot::update(float d)
{
	this->setPosition(getPosition().x + speed, getPosition().y);
	distance += speed;
	if (hitCheck() || distance >= 500)
	{
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		auto layer = nowScene->getChildByName("PLLayer");
		if (type == CharaType::ENEMY)
		{
			layer = nowScene->getChildByName("EMLayer");
		}
		layer->removeChild(this);
	}
}

bool Shot::hitCheck()
{
	////	キャラクターとの判定
	//auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
	//auto layer = nowScene->getChildByName("EMLayer");
	//if (type == CharaType::ENEMY)
	//{
	//	layer = nowScene->getChildByName("PLLayer");
	//}

	//for (auto obj : layer->getChildren())
	//{
	//	//	判定用BOX
	//	auto objBox = obj->boundingBox();
	//	auto charaBox = this->boundingBox();

	//	if (charaBox.intersectsRect(objBox))
	//	{
	//		//	当たった場合はダメージ硬直
	//		return true;
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
		return true;
	}
	return false;
}

