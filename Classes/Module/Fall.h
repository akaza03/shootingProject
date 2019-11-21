#pragma once
#include <cocos2d.h>

struct Fall
{
	bool operator() (cocos2d::Sprite & sp, ActData &act);
};

