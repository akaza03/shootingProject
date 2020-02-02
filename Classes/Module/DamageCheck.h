#pragma once
#include <cocos2d.h>

struct DamageCheck
{
	bool operator()(cocos2d::Sprite & sp, struct ActData &act);
private:
	void DoDamage(cocos2d::Sprite & sp, ActData & act);				//	ダメージを与える処理
};

