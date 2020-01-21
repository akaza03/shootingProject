#pragma once
#include "Character.h"

class Enemy :
	public Character
{
public:
	Enemy();
	~Enemy();
	void update(float d);
	CREATE_FUNC(Enemy);
private:
	bool playerSearch(ActData &act);				//	�v���C���[�𔭌����鏈��
	void objTurn(ActData &act);						//	�I�u�W�F�N�g�Ƃ̐ڐG���Ɉړ������̕ύX
	void typeUpdate(ActData &act);					//	charaID���Ƃ̏���
};

