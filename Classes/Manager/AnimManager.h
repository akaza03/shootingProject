#pragma once
#include <map>
#include "cocos2d.h"
#include "Unit/charaStruct.h"
#include "Unit/Character.h"

#define lpAnimMng AnimManager::GetInstance()

using AnimMap = std::map < std::string, cocos2d::Action* >;

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
	//	�摜�p�X,�摜�S�̂̕�����,�����J�nID,�A�j���[�V�����̕�����,�t���[����,���[�v���邩�ǂ���
	cocos2d::Animation* AnimationCreate(std::string imagePass, cocos2d::Vec2 divCnt, cocos2d::Vec2 startID, int animCntMax, float frame, bool loop);
	
	//	�A�j���[�V�����̊J�n
	void AnimRun(cocos2d::Sprite* sprite, AnimState anim, CharaType type, AnimMap &charaAnim);

	//	�L�����N�^�[�ɃA�j���[�V��������n��
	void SetAnim(CharaType type, int id, AnimMap &anim);
private:
	AnimManager();
	void AnimationInit();										//	�A�j���[�V�����̓o�^�p

	std::string GetAnimName(AnimState anim);					//	�A�j���[�V�����J�n���̃A�j���[�V�������擾�p

	void AnimCountPlus(AnimMap &anim);							//	�Q�ƃJ�E���g�𑝂₷

	std::map < std::string, cocos2d::Animation* > _animMap;		//	�A�j���[�V�����������[

	static AnimManager* s_Instance;
};
