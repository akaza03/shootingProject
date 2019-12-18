#include "Unit/Character.h"
#include "Unit/Shot.h"
#include "Shooting.h"

bool Shooting::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (act.attackCnt == 0 && act.nowAnim == AnimState::RSHOT)
	{
		auto shotSprite = RES_ID("p0Shot");
		//	UŒ‚‚·‚éƒLƒƒƒ‰‚É‚æ‚Á‚Ä’e‚Ì•ÏX&UŒ‚ŠÔŠu‚Ì•ÏX
		if (act.cType == CharaType::PLAYER)
		{
			switch (act.charaID)
			{
				case 0:
					shotSprite = RES_ID("p0Shot");
					act.attackCnt = 10;
					break;
				case 1:
					shotSprite = RES_ID("p1Shot");
					act.attackCnt = 20;
					break;
				case 2:
					shotSprite = RES_ID("p2Shot");
					act.attackCnt = 30;
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
	}

	//	ƒJƒEƒ“ƒg‚ª0‚Å‚È‚¢ê‡UŒ‚‚ÌƒJƒEƒ“ƒg‚ğŒ¸‚ç‚·
	if (act.attackCnt > 0)
	{
		act.attackCnt--;
	}

	return false;
}
