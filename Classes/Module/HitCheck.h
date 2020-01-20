#pragma once
#include <cocos2d.h>

struct HitCheck
{
	bool operator()(cocos2d::Sprite & sp, struct ActData &act);
};
