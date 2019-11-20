#pragma once
#include "OprtState.h"

//enum INPUT_KEY
//{
//	LEFT,
//	RIGHT,
//	UP,
//	DOWN,
//	INPUT_MAX
//};
//
//using inputMap = std::vector<INPUT_KEY, int>;

class OprtKey
	:public OprtState
{
public:
	OprtKey();
	~OprtKey();
	cocos2d::EventListener* oprtInit(cocos2d::Sprite *sprite, int speed);
	void update();
};

