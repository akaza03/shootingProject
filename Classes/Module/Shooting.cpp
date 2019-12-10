#include "Unit/Character.h"
#include "Unit/Shot.h"
#include "Shooting.h"

bool Shooting::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (act.attackCnt >= 10)
	{
		act.attackCnt = 0;
	}

	if (act.attackCnt == 0)
	{
		if (act.nowAnim == AnimState::RSHOT)
		{
			auto shot = Shot::create();
			shot->SetInit("image/Sprites/Fx/power-up/power-up-1.png", sp, act);
			act.attackCnt++;
		}
	}

	if (act.attackCnt > 0)
	{
		act.attackCnt++;
	}

	return false;
}
