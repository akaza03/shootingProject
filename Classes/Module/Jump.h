#pragma once
#include <cocos2d.h>

struct Jump
{
	bool operator()(cocos2d::Sprite & sp, struct ActData &act);
};
