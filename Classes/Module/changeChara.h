#pragma once
#include <cocos2d.h>

struct changeChara
{
	bool operator() (cocos2d::Sprite & sp, ActData &act);
};

