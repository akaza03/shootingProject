#include "Unit/Character.h"
#include "_DebugOut/_DebugConOut.h"
#include "HitCheck.h"


bool HitCheck::operator()(cocos2d::Sprite & sp, ActData &act)
{
	//	衝突用のレイヤーの取得
	auto director = cocos2d::Director::getInstance();
	auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BGLayer")->getChildByName("stageMap");
	auto layerMap = map->getLayer("collision");

	//	プレイヤーの座標
	auto pos = cocos2d::Vec2(sp.getPosition().x, layerMap->getLayerSize().height * layerMap->getMapTileSize().height - sp.getPosition().y);
	//	指定された場所のタイルID
	int tile = 0;

	//	マップとの当たり判定
	//	下
	auto DownPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width, (pos.y + sp.getContentSize().height / 2) / layerMap->getMapTileSize().height);
	tile = GetTile(DownPos, layerMap);
	if (tile != 0)
	{
		TRACE("下%d", tile);
		act.checkPoint[DIR::DOWN] = true;
	}
	else
	{
		act.checkPoint[DIR::DOWN] = false;
	}

	//	上
	auto UpPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width, pos.y / layerMap->getMapTileSize().height - 1);
	tile = GetTile(UpPos, layerMap);
	if (tile != 0)
	{
		TRACE("上%d", tile);
		act.checkPoint[DIR::UP] = true;
	}
	else
	{
		act.checkPoint[DIR::UP] = false;
	}

	// 左
	auto LPos = cocos2d::Vec2((pos.x - sp.getContentSize().width / 2) / layerMap->getMapTileSize().width, pos.y / layerMap->getMapTileSize().height);
	tile = GetTile(LPos, layerMap);
	if (tile != 0)
	{
		TRACE("左%d", tile);
		act.checkPoint[DIR::LEFT] = true;
	}
	else
	{
		LPos.y = (pos.y + sp.getContentSize().height / 3) / layerMap->getMapTileSize().height;

		tile = GetTile(LPos, layerMap);

		if (tile != 0)
		{
			TRACE("左%d", tile);
			act.checkPoint[DIR::LEFT] = true;
		}
		else
		{
			act.checkPoint[DIR::LEFT] = false;
		}
	}

	//	右
	auto RPos = cocos2d::Vec2((pos.x + sp.getContentSize().width / 2) / layerMap->getMapTileSize().width, pos.y / layerMap->getMapTileSize().height);
	tile = GetTile(RPos, layerMap);
	if (tile != 0)
	{
		TRACE("右%d", tile);
		act.checkPoint[DIR::RIGHT] = true;
	}
	else
	{
		RPos.y = (pos.y + sp.getContentSize().height / 3) / layerMap->getMapTileSize().height;

		tile = GetTile(RPos, layerMap);

		if (tile != 0)
		{
			TRACE("右%d", tile);
			act.checkPoint[DIR::RIGHT] = true;
		}
		else
		{
			act.checkPoint[DIR::RIGHT] = false;
		}
	}
	
	return false;
}

int HitCheck::GetTile(cocos2d::Vec2 _pos, cocos2d::TMXLayer * _layer)
{
	//	取得場所が画面外の場合は0を返す
	if (_pos.x > 0 && _pos.x < _layer->getLayerSize().width
		&&	_pos.y > 0 && _pos.y < _layer->getLayerSize().height)
	{
		//	タイルの取得
		return _layer->getTileGIDAt(_pos);
	}
	return 0;
}
