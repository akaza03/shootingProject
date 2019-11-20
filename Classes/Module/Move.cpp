#include "Unit/Character.h"
#include "Move.h"

bool Move::operator()(cocos2d::Sprite & sp, ActData & act)
{
	act.distance.x = 0;
	if (act.key[UseKey::K_LEFT].first && act.key[UseKey::K_LEFT].second)
	{
		if (!act.checkPoint[DIR::LEFT])
		{
			act.distance.x = - act.speed;
		}
	}
	if (act.key[UseKey::K_RIGHT].first && act.key[UseKey::K_RIGHT].second)
	{
		if (!act.checkPoint[DIR::RIGHT])
		{
			act.distance.x = act.speed;
		}
	}

	return false;
}
