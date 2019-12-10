#include "Unit/Character.h"
#include "OldKeyUpdate.h"


bool OldKeyUpdate::operator()(cocos2d::Sprite & sp, ActData & act)
{
	for (auto itrKey : UseKey())
	{
		//	���̃A�j���[�V�����Ɍ��݂̃A�j���[�V�����̃L�[����n��
		std::get<1>(act.key[itrKey]) = std::get<0>(act.key[itrKey]);
	}
	return false;
}
