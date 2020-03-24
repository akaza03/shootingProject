#include "Unit/Character.h"
#include "Move.h"

bool Move::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto dis = 0;
	if (act.anim != AnimState::DAMAGE)
	{
		//	���ړ�
		if (std::get<0>(act.key[UseKey::K_LEFT]) 
			&& std::get<2>(act.key[UseKey::K_LEFT]))
		{
			//	���ɏ�Q�����Ȃ��ꍇ
			if (!act.checkPoint[DIR::LEFT])
			{
				dis -= act.speed.x;
			}
		}
		//	�E�ړ�
		if (std::get<0>(act.key[UseKey::K_RIGHT]) 
			&& std::get<2>(act.key[UseKey::K_RIGHT]))
		{
			//	�E�ɏ�Q�����Ȃ��ꍇ
			if (!act.checkPoint[DIR::RIGHT])
			{
				dis += act.speed.x;
			}
		}
	}
	act.distance.x = dis;

	return false;
}
