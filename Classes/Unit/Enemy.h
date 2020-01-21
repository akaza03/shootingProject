#pragma once
#include "Character.h"

class Enemy :
	public Character
{
public:
	Enemy();
	~Enemy();
	void update(float d);
	CREATE_FUNC(Enemy);
private:
	bool playerSearch(ActData &act);				//	プレイヤーを発見する処理
	void objTurn(ActData &act);						//	オブジェクトとの接触時に移動方向の変更
	void typeUpdate(ActData &act);					//	charaIDごとの処理
};

