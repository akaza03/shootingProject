#pragma once
#include <cocos2d.h>

struct HitCheck
{
	bool operator()(cocos2d::Sprite & sp, struct ActData &act);

	int GetTile(cocos2d::Vec2 _pos, cocos2d::TMXLayer *_layer);
};
