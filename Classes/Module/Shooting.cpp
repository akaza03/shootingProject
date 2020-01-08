#include "Unit/Character.h"
#include "Unit/Shot.h"
#include "Shooting.h"

bool Shooting::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (act.attackCnt == 0 && act.nowAnim == AnimState::RSHOT)
	{
		//	�e�̎��
		auto shotSprite = RES_ID("p0Shot");
		//	�e�̃X�s�[�h
		float speed = 0;

		//	�U������L�����ɂ���Ēe�̕ύX&�U���Ԋu�̕ύX
		if (act.cType == CharaType::PLAYER)
		{
			switch (act.charaID)
			{
				case 0:
					shotSprite = RES_ID("p0Shot");
					act.attackCnt = 10;
					speed = 8;
					break;
				case 1:
					shotSprite = RES_ID("p1Shot");
					act.attackCnt = 5;
					speed = 10;
					break;
				case 2:
					shotSprite = RES_ID("p2Shot");
					act.attackCnt = 20;
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
			speed = 10;
		}

		auto shot = Shot::create();
		shot->SetInit(shotSprite, sp, act, speed);
	}

	//	�J�E���g��0�łȂ��ꍇ�U���̃J�E���g�����炷
	if (act.attackCnt > 0)
	{
		act.attackCnt--;
	}

	return false;
}
