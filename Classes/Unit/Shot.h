#pragma once
#include <cocos2d.h>

class Shot
	:public cocos2d::Sprite
{
public:
	Shot();
	~Shot();
	//	�摜�p�X,���˃L�����̃X�v���C�g,���˃L�����̏��
	void SetInit(std::string ImagePass, cocos2d::Sprite & sp, ActData &chara);
	void update(float d);
	CREATE_FUNC(Shot);

private:
	float speed = 0;						//	�e�̃X�s�[�h
	CharaType type;							//	���ꂪ�������e��
	float distance = 0;						//	�ړ���������

	bool hitCheck();
};

