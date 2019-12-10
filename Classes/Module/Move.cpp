#include "Unit/Character.h"
#include "Move.h"

bool Move::operator()(cocos2d::Sprite & sp, ActData & act)
{
	act.distance.x = 0;
	if (std::get<0>(act.key[UseKey::K_LEFT]) && std::get<2>(act.key[UseKey::K_LEFT]))
	{
		if (!act.checkPoint[DIR::LEFT])
		{
			act.distance.x = -act.speed.x;
		}
	}
	if (std::get<0>(act.key[UseKey::K_RIGHT]) && std::get<2>(act.key[UseKey::K_RIGHT]))
	{
		if (!act.checkPoint[DIR::RIGHT])
		{
			act.distance.x = act.speed.x;
		}
	}

	return false;
}
