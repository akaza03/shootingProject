#include "Unit/Character.h"
#include "Unit/Shot.h"
#include "Shooting.h"

bool Shooting::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (act.attackCnt == 0 && act.nowAnim == AnimState::RSHOT)
	{
		//	弾の種類
		auto shotSprite = RES_ID("p0Shot");
		//	弾の攻撃力
		float power = 0;
		//	弾のスピード
		float speed = 0;

		//	攻撃するキャラによって弾の変更&攻撃間隔の変更
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

	//	カウントが0でない場合攻撃のカウントを減らす
	if (act.attackCnt > 0)
	{
		act.attackCnt--;
	}

	return false;
}
