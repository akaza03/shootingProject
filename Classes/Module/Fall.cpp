#include "Unit/Character.h"
#include "Fall.h"

bool Fall::operator()(cocos2d::Sprite & sp, ActData & act)
{
	//	重力を加算する
	float gy = -0.3f;
	if (act.anim == AnimState::DAMAGE)
	{
		act.Gravity = 0;
	}
	else
	{
		act.Gravity += gy;
	}

	//	足場がある場合は重力を0に
	if (abs(act.distance.y) < abs(act.Gravity) && act.checkPoint[DIR::DOWN])
	{
		act.Gravity = 0;
		act.jumpFlag = false;
	}

	//	空中でのめり込み防止処理
	if (act.Gravity != 0)
	{
		if (act.checkPoint[DIR::LEFT] && act.dir == DIR::LEFT)
		{
			act.distance.x = 0;
		}
		else if (act.checkPoint[DIR::RIGHT] && act.dir == DIR::RIGHT)
		{
			act.distance.x = 0;
		}
	}

	return false;
}
