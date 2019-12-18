#include "Unit/Character.h"
#include "Jump.h"

bool Jump::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (!act.jumpFlag)
	{
		act.jumpCnt = act.jumpMax;
		act.distance.y = 0;

		//	�W�����v�J�n
		if (std::get<0>(act.key[UseKey::K_UP]) && std::get<2>(act.key[UseKey::K_UP]))
		{
			act.jumpFlag = true;
			lpEffectManager.SetEffect("effect/Laser01.efk", "FGLayer", sp.getPosition(), 20, true);
			lpAudioManager.SetBank("Sound.ckb", "shot", SoundType::S_SE);
		}
	}

	if (act.jumpFlag)
	{
		//	jumpCnt�̐������W�����v�ł���悤�ɐ���
		if (act.distance.y == 0 && std::get<0>(act.key[UseKey::K_UP]))
		{
			act.jumpCnt--;
		}

		//	�����鏈��
		if (act.checkPoint[DIR::UP] || !std::get<0>(act.key[UseKey::K_UP]))
		{
			act.distance.y = 0;
		}
		//	�W�����v�\�񐔂𒴂��Ă��Ȃ�������W�����v����
		else if (act.jumpCnt >= -1)
		{
			act.distance.y = act.speed.y;
		}
	}
	return false;
}
