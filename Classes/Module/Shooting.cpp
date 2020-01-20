#include "Unit/Character.h"
#include "Unit/Shot.h"
#include "Shooting.h"

bool Shooting::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (act.attackCnt == 0 && act.nowAnim == AnimState::RSHOT)
	{
		//	’e‚Ìí—Ş
		auto shotSprite = RES_ID("p0Shot");
		//	’e‚ÌUŒ‚—Í
		float power = 0;
		//	’e‚ÌƒXƒs[ƒh
		float speed = 0;

		//	UŒ‚‚·‚éƒLƒƒƒ‰‚É‚æ‚Á‚Ä’e‚Ì•ÏX&UŒ‚ŠÔŠu‚Ì•ÏX
		if (act.cType == CharaType::PLAYER)
		{
			switch (act.charaID)
			{
				case 0:
					shotSprite = RES_ID("p0Shot");
					act.attackCnt = 10;
					power = 10;
					speed = 8;
					break;
				case 1:
					shotSprite = RES_ID("p1Shot");
					act.attackCnt = 5;
					power = 5;
					speed = 10;
					break;
				case 2:
					shotSprite = RES_ID("p2Shot");
					act.attackCnt = 20;
					power = 20;
					speed = 6;
					break;
				default:
					int a = 0;
					break;
			}
		}
		else
		{
			shotSprite = RES_ID("p0Shot");
			act.attackCnt = 30;
			power = 10;
			speed = 10;
		}

		auto shot = Shot::create();
		shot->SetInit(shotSprite, sp, act, power, speed);
	}

	//	ƒJƒEƒ“ƒg‚ª0‚Å‚È‚¢ê‡UŒ‚‚ÌƒJƒEƒ“ƒg‚ğŒ¸‚ç‚·
	if (act.attackCnt > 0)
	{
		act.attackCnt--;
	}

	return false;
}
