#include "Unit/Character.h"
#include "AnimUpdate.h"

bool AnimUpdate::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto anim = AnimState::IDLE;
	if (act.damageCnt > 0)
	{
		anim = AnimState::DAMAGE;
	}
	else if (act.key[UseKey::K_SPACE].first)
	{
		anim = AnimState::RSHOT;
	}
	else if (act.jumpFlag)
	{
		anim = AnimState::JUMP;
	}
	else if (act.distance.x != 0 || act.key[UseKey::K_LEFT].first || act.key[UseKey::K_RIGHT].first)
	{
		anim = AnimState::RUN;
	}
	else
	{
		anim = AnimState::IDLE;
	}

	act.nowAnim = anim;

	return false;
}
