#pragma once
#include <cocos2d.h>

struct Shooting
{
	bool operator()(cocos2d::Sprite & sp, ActData & act);
};

