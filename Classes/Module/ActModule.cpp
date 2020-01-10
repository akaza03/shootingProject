#include "Unit/Character.h"
#include "ActModule.h"

void ActModule::operator()(cocos2d::Sprite & sp, ActData & act)
{
	//	�ړ�����
	Jump()(sp, act);
	Move()(sp, act);
	Fall()(sp, act);

	//	�A�j���[�V�����̍X�V
	AnimUpdate()(sp, act);
	//	�����̍X�V
	DirCheck()(sp, act);
	//	�ړ�
	SetPos()(sp, act);

	//	�e����
	Shooting()(sp, act);

	//	�L�����N�^�[�̐؂�ւ�
	changeChara()(sp, act);

	//	�L�[�̍X�V
	OldKeyUpdate()(sp, act);

	//	�����蔻��
	HitCheck()(sp, act);
	DamageCheck()(sp, act);
}
