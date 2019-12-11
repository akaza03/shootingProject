#include "Unit/Character.h"
#include "Unit/Shot.h"
#include "Shooting.h"

bool Shooting::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (act.attackCnt >= 10)
	{
		act.attackCnt = 0;
	}

	if (act.attackCnt == 0 && act.nowAnim == AnimState::RSHOT)
	{
		auto shotSprite = RES_ID("p0Shot");
		//	UŒ‚‚·‚éƒLƒƒƒ‰‚É‚æ‚Á‚Ä’e‚Ì•ÏXv
		if (act.cType == CharaType::PLAYER)
		{
			switch (act.charaID)
			{
				case 0:
					shotSprite = RES_ID("p0Shot");
					break;
				case 1:
					shotSprite = RES_ID("p1Shot");
					break;
				case 2:
					shotSprite = RES_ID("p2Shot");
					break;
				default:
					int a = 0;
					break;
			}
		}
		else
		{
			shotSprite = RES_ID("p0Shot");
		}

		auto shot = Shot::create();
		shot->SetInit(shotSprite, sp, act);
		act.attackCnt++;
	}

	if (act.attackCnt > 0)
	{
		act.attackCnt++;
	}

	return false;
}
