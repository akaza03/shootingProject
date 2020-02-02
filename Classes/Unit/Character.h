#pragma once
#include <functional>
#include "Manager/ResourceManager.h"
#include "Module/ActSet.h"
#include "Manager/AnimManager.h"
#include "Input/UseKey.h"
#include "Module/ActModule.h"
#include "Input/OprtState.h"
#include "Manager/AudioManager.h"
#include "Manager/EffManager.h"

class OprtState;

//using spPointer = bool (*)(cocos2d::Sprite);
using actionPoint = std::function<bool(cocos2d::Sprite&,struct ActData&)>;

using hitList = std::map<DIR, bool>;												//	�����蔻��p���X�g

using AnimMap = std::map < std::string, cocos2d::Action* >;							//	�A�j���[�V�����i�[�p���X�g
using changeList = std::vector<int>;												//	�L�����`�F���W���̃J�E���g�p���X�g

//	���݂̃L�[,1�t���[���O�̃L�[,�o�^����Ă��邩�ǂ���
using keyList = std::map<UseKey, std::tuple<bool, bool, bool>>;						//	�L�[�p�̃��X�g

//	�L�����N�^�[�̏��p
struct ActData
{
	int HP = 1;													//	�̗�
	int MaxHP = 1;												//	�ő�HP
	int damageNumber = 0;										//	��e�_���[�W
	bool dirInver = false;										//	�����]������ꍇ��true
	cocos2d::Vec2 speed;										//	�ړ��X�s�[�h(����,�W�����v)
	float Gravity = 0;											//	�d��
	keyList key;												//	�ǂ̃L�[���������珈������̂�(List)
	AnimState anim;												//	���g�̃A�j���[�V����
	AnimState nowAnim = AnimState::IDLE;						//	���݂̃A�j���[�V����
	DIR dir = DIR::RIGHT;										//	���݂̌���
	hitList checkPoint;											//	��Q���Ƃ̓����蔻��p
	int damageCnt = 0;											//	�_���[�W���󂯂����̍d���p
	int invTime = 0;											//	���G����
	cocos2d::Vec2 distance = { 0,0 };							//	�ړ�����
	bool jumpFlag = false;										//	�W�����v�����ǂ����̃t���O
	int jumpCnt = 1;											//	��x�ɃW�����v���ł����
	int jumpMax;												//	�W�����v�񐔃��Z�b�g�p
	int attackCnt = 0;											//	�U�����Ă���̌o�ߎ���(Shot����ȂǂŎg�p)
	CharaType cType;											//	�L�����N�^�[�̃^�C�v
	int charaID;												//	�L�����N�^�[�̎�ޔ��ʗp��ID
	changeList changeCnt;										//	�L�����`�F���W���̃J�E���g�p���X�g
	cocos2d::Vec2 touchPos;										//	�L�����`�F���W�����̃^�b�`���W
	float searchDisAtk;											//	�G�p�U���J�n����(x���W)
	cocos2d::Vec2 searchDisDir;									//	�G�p�v���C���[����������(x���W,y���W)
	bool superArmor;											//	�U�����󂯂����Ђ�܂Ȃ����ǂ���
	bool dirFixed;												//	�����]���o���邩�ǂ���(false���Ɠ�����������������)
};

class Character
	:public cocos2d::Sprite
{
public:
	Character();
	virtual ~Character();
	virtual void update(float d) = 0;

	bool SetInit(DIR stdir, int id, cocos2d::Vec2 pos, int hp, cocos2d::Vec2 speed,
					cocos2d::Scene *scene, float disAtk, cocos2d::Vec2 disDir, bool armor, bool dirFix);

	AnimState CheckAnim();															//	�A�j���[�V�����m�F�p

private:
	void InitActData(cocos2d::Vec2 speed);											//	ActData�̏�����

protected:
	OprtState *_oprtState;															//	���쐧��
	ActData _actData;																//	�L�����N�^�[�̏��p
	std::map<const char *,ActData> _charaList;										//	�L�����N�^�[�̏��p���X�g

	cocos2d::Vec2 oldTouchPos;

	AnimMap _animMap;

	//std::list<cocos2d::EventKeyboard::KeyCode> _keyList;							//	�L�[�p�̃��X�g

	//std::list<actionPoint> _actList;												//	�A�N�V�����̊Ǘ��p

	//bool(*_act)(cocos2d::Sprite&, ActData &);										//	�֐��|�C���^
};
