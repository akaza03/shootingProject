#include "Unit/Character.h"
#include "Fall.h"

bool Fall::operator()(cocos2d::Sprite & sp, ActData & act)
{
	//	d—Í‚ğ‰ÁZ‚·‚é
	float gy = -0.1f;
	if (act.anim == AnimState::DAMAGE)
	{
		act.Gravity = 0;
	}
	else
	{
		act.Gravity += gy;
	}

	//	‘«ê‚ª‚ ‚éê‡‚Íd—Í‚ğ0‚É
	if (abs(act.distance.y) < abs(act.Gravity) && act.checkPoint[DIR::DOWN])
	{
		act.Gravity = 0;
		act.jumpFlag = false;
	}

	//	‹ó’†‚Å‚Ì‚ß‚è‚İ–h~ˆ—
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
