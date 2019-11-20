#pragma once
#include <map>
#include "cocos2d.h"
#include "Unit/charaStruct.h"
#include "Unit/Character.h"

#define lpAnimManager AnimManager::GetInstance()

class Character;

class AnimManager
{
public:
	static AnimManager& GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new AnimManager();
		}
		return *s_Instance;
	}
	~AnimManager();

	//	�A�j���[�V�����̓o�^
	//	�摜�p�X,�摜�S�̂̕�����,�����J�nID,�A�j���[�V�����̕�����,�t���[����
	cocos2d::Action* AnimationCreate(std::string imagePass, cocos2d::Vec2 divCnt, cocos2d::Vec2 startID, int animCntMax, float frame, bool loop);

	void AnimRun(cocos2d::Sprite* sprite, AnimState anim, CharaType type);		//	�A�j���[�V�����̊J�n

	AnimState AnimStateUpdate(struct ActData &act);								//	�X�e�[�g�̃A�b�v�f�[�g
private:
	AnimManager();
	void AnimationInit();														//	�A�j���[�V�����̓o�^�p

	std::string GetAnimName(AnimState anim, CharaType type);					//	�A�j���[�V�����J�n���̃A�j���[�V�������擾�p

	void AnimCountPlus();														//	�Q�ƃJ�E���g�𑝂₷

	std::map < std::string, cocos2d::Action* > _animMap;						//	�A�j���[�V�����������[
	static AnimManager* s_Instance;
};
