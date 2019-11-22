#include "Unit/Character.h"
#include "Jump.h"

bool Jump::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (!act.jumpFlag)
	{
		act.jumpCnt = act.jumpMax;
		act.distance.y = 0;

		//	ジャンプ開始
		if (act.key[UseKey::K_UP].first && act.key[UseKey::K_UP].second)
		{
			act.jumpFlag = true;
		}
	}

	if (act.jumpFlag)
	{
		//	jumpCntの数だけジャンプできるように制御
		if (act.distance.y == 0 && act.key[UseKey::K_UP].first)
		{
			act.jumpCnt--;
		}

		//	落ちる処理
		if (act.checkPoint[DIR::UP] || !act.key[UseKey::K_UP].first)
		{
			act.distance.y = 0;
		}
		//	ジャンプ可能回数を超えていなかったらジャンプする
		else if (act.jumpCnt >= -1)
		{
			act.distance.y = act.speed.y;
		}
	}
	return false;
}
