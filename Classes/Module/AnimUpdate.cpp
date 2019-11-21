#include "Unit/Character.h"
#include "AnimUpdate.h"

bool AnimUpdate::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto anim = AnimState::IDLE;
	if (act.skyflag)
	{
		anim = AnimState::JUMP;
	}
	else if (act.distance.x != 0)
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
