#pragma once
#include "OprtState.h"

class OprtTouch
	:public OprtState
{
public:
	OprtTouch();
	~OprtTouch();
	cocos2d::EventListener* oprtInit();
	void update();

private:
	void checkKey(cocos2d::Vec2 touchPos);									//	�L�[�̔���

	cocos2d::Vec2 _startTouchPos;											//	�^�b�`�J�n���̍��W
};

