#include "Unit/Character.h"
#include "Jump.h"

bool Jump::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (!act.jumpFlag)
	{
		act.jumpCnt = act.jumpMax;
		act.distance.y = 0;

		//	ジャンプ開始
		if (std::get<0>(act.key[UseKey::K_UP]) && std::get<2>(act.key[UseKey::K_UP]))
		{
			act.jumpFlag = true;
			lpEffectManager.SetEffect("effect/Laser01.efk", "FGLayer", sp.getPosition(), 20, true);
			lpAudioManager.SetBank("Sound.ckb", "shot", SoundType::S_SE);
		}
	}

	if (act.jumpFlag)
	{
		//	jumpCntの数だけジャンプできるように制御
		if (act.distance.y == 0 && std::get<0>(act.key[UseKey::K_UP]))
		{
			act.jumpCnt--;
		}

		//	落ちる処理
		if (act.checkPoint[DIR::UP] || !std::get<0>(act.key[UseKey::K_UP]))
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
