#include "Unit/Character.h"
#include "Move.h"

bool Move::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto dis = 0;
	if (act.anim != AnimState::DAMAGE)
	{
		//	¶ˆÚ“®
		if (std::get<0>(act.key[UseKey::K_LEFT]) 
			&& std::get<2>(act.key[UseKey::K_LEFT]))
		{
			//	¶‚ÉáŠQ•¨‚ª‚È‚¢ê‡
			if (!act.checkPoint[DIR::LEFT])
			{
				dis -= act.speed.x;
			}
		}
		//	‰EˆÚ“®
		if (std::get<0>(act.key[UseKey::K_RIGHT]) 
			&& std::get<2>(act.key[UseKey::K_RIGHT]))
		{
			//	‰E‚ÉáŠQ•¨‚ª‚È‚¢ê‡
			if (!act.checkPoint[DIR::RIGHT])
			{
				dis += act.speed.x;
			}
		}
	}
	act.distance.x = dis;

	return false;
}
