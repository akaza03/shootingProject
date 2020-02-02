#include "Unit/Character.h"
#include "AnimUpdate.h"

bool AnimUpdate::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (act.nowAnim != AnimState::THROW)
	{
		auto anim = AnimState::IDLE;
		if (act.damageCnt > 0 && !act.superArmor)
		{
			anim = AnimState::DAMAGE;
		}
		else if (std::get<1>(act.key[UseKey::K_SPACE]))
		{
			anim = AnimState::RSHOT;
		}
		else if (act.jumpFlag)
		{
			anim = AnimState::JUMP;
		}
		else if (act.distance.x != 0 || std::get<1>(act.key[UseKey::K_LEFT]) || std::get<1>(act.key[UseKey::K_RIGHT]))
		{
			anim = AnimState::RUN;
		}

		if (act.nowAnim == AnimState::DIE)
		{
			anim = AnimState::DIE;
		}


		act.nowAnim = anim;
	}

	return false;
}
