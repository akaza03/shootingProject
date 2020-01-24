#include "Unit/Character.h"
#include "Unit/Shot.h"
#include "Shooting.h"

bool Shooting::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (act.attackCnt == 0 && act.nowAnim == AnimState::RSHOT)
	{
		//	�e�̎��
		auto shotSprite = RES_ID("p0Shot");
		//	�e�̍U����
		float power = 0;
		//	�e�̃X�s�[�h
		float speed = 0;
		//	��e���̍d������
		float stunTime = 0;

		//	�U������L�����ɂ���Ēe�̕ύX&�U���Ԋu�̕ύX
		if (act.cType == CharaType::PLAYER)
		{
			switch (act.charaID)
			{
				case 0:
					shotSprite = RES_ID("p0Shot");
					act.attackCnt = 10;
					power = 10;
					speed = 8;
					stunTime = 20;
					break;
				case 1:
					shotSprite = RES_ID("p1Shot");
					act.attackCnt = 5;
					power = 5;
					speed = 10;
					stunTime = 20;
					break;
				case 2:
					shotSprite = RES_ID("p2Shot");
					act.attackCnt = 20;
					power = 20;
					speed = 6;
					stunTime = 20;
					break;
				default:
					break;
			}
		}
		else
		{
			switch (act.charaID)
			{
				case 0:
					shotSprite = RES_ID("p0Shot");
					act.attackCnt = 50;
					power = 10;
					speed = 5;
					stunTime = 20;
					break;
				case 1:
					shotSprite = RES_ID("p1Shot");
					act.attackCnt = 10;
					power = 5;
					speed = 10;
					stunTime = 20;
					break;
				case 2:
					shotSprite = RES_ID("p2Shot");
					act.attackCnt = 10;
					power = 20;
					speed = 5;
					stunTime = 100;
					break;
				default:
					break;
			}
		}

		auto shot = Shot::create();
		shot->SetInit(shotSprite, sp, act, power, speed, stunTime);
	}

	//	�J�E���g��0�łȂ��ꍇ�U���̃J�E���g�����炷
	if (act.attackCnt > 0)
	{
		act.attackCnt--;
	}

	return false;
}
