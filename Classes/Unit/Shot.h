#pragma once
#include <cocos2d.h>

class Shot
	:public cocos2d::Sprite
{
public:
	Shot();
	~Shot();
	//	�摜�p�X,���˃L�����̃X�v���C�g,���˃L�����̏��,�e�̍U����,�e�̃X�s�[�h,��e���̍d������
	void SetInit(std::string ImagePass, cocos2d::Sprite & sp, ActData &chara, float sPower, float sSpeed, float stun);
	void update(float d);

	CharaType GetType();
	int GetID();
	float GetPower();
	float GetSpeed();
	float GetStunTime();
	bool GetAtkFlag();
	bool GetThrow();
	void SetHitChara(bool flag);

	CREATE_FUNC(Shot);

private:
	float power = 0;						//	�e�̍U����
	float speed = 0;						//	�e�̃X�s�[�h
	float stunTime;							//	��e���̍d������
	CharaType type;							//	���ꂪ�������e��
	int charaID;
	bool atkFlag;							//	�U�����肪���邩�ǂ���
	float distance = 0;						//	�ړ���������
	bool hitChara;							//	�L�����Ƃ̓����蔻��
	bool hitObj;							//	�n�`�Ƃ̓����蔻��

	bool throwFlag;							//	�����Z�̏ꍇ��true

	void TypeInit(ActData &chara);			//	charaType���Ƃ�Init����
	void TypeUpdate();						//	charaType���Ƃ�update����
	void HitCheck();
};

