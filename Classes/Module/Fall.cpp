#include "Unit/Character.h"
#include "Fall.h"

bool Fall::operator()(cocos2d::Sprite & sp, ActData & act)
{
	//	重力を加算する
	float gy = -0.05f;
	act.Gravity += gy;

	//	足場がある場合は重力を0に
	if (act.checkPoint[DIR::DOWN])
	{
		act.Gravity = 0;
		act.skyflag = false;
	}

	return false;
}
