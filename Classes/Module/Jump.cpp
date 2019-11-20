#include "Unit/Character.h"
#include "Jump.h"

bool Jump::operator()(cocos2d::Sprite & sp, ActData & act)
{
	act.distance.y = 0;
	if (act.key[UseKey::K_UP].first && act.key[UseKey::K_UP].second)
	{
		if (!act.checkPoint[DIR::UP])
		{
			act.distance.y = act.speed;
		}
	}

	return false;
}
