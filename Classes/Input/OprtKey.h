#pragma once
#include "OprtState.h"

class OprtKey
	:public OprtState
{
public:
	OprtKey();
	~OprtKey();
	cocos2d::EventListener* oprtInit(cocos2d::Sprite *sprite);
	void update();
};

