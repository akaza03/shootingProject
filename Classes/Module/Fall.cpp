#include "Unit/Character.h"
#include "Fall.h"

bool Fall::operator()(cocos2d::Sprite & sp, ActData & act)
{
	//	d—Í‚ğ‰ÁZ‚·‚é
	float gy = -0.05f;
	act.Gravity += gy;

	//	‘«ê‚ª‚ ‚éê‡‚Íd—Í‚ğ0‚É
	if (act.checkPoint[DIR::DOWN])
	{
		act.Gravity = 0;
		act.skyflag = false;
	}

	return false;
}
