#include "Unit/Character.h"
#include "Jump.h"

bool Jump::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (act.key[UseKey::K_UP].first && act.key[UseKey::K_UP].second && !act.skyflag)
	{
		act.skyflag = true;
	}
	if (act.skyflag)
	{
		if (act.checkPoint[DIR::UP] || !act.key[UseKey::K_UP].first)
		{
			act.distance.y = 0;
		}
		else
		{
			act.distance.y = act.speed.y;
		}
	}
	else
	{
		act.distance.y = 0;
	}
	return false;
}
