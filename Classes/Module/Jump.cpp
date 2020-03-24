#include "Unit/Character.h"
#include "Jump.h"

bool Jump::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (!act.jumpFlag)
	{
		act.distance.y = 0;
	}

	if ((!act.jumpFlag && act.anim != AnimState::DAMAGE)
		|| (!act.checkPoint[DIR::DOWN] && act.jumpCnt >= 0))
	{
		//	ジャンプ開始
		if (std::get<0>(act.key[UseKey::K_UP]) && std::get<2>(act.key[UseKey::K_UP]))
		{
			act.jumpCnt = act.jumpMax;
			act.jumpFlag = true;
			act.jumpCnt--;
		}
	}

	if (act.jumpFlag)
	{
		if (act.anim == AnimState::DAMAGE)
		{
			act.jumpFlag = false;
		}
		else
		{
			//	頭上判定
			if (act.checkPoint[DIR::UP] && act.distance.y >= 0)
			{
				act.Gravity = -act.speed.y + act.Gravity;
				act.distance.y = act.speed.y;
			}
			//	ジャンプ可能回数を超えていなかったらジャンプする
			else if (act.jumpCnt >= 0)
			{
				act.distance.y = act.speed.y;
			}
		}
	}
	return false;
}
