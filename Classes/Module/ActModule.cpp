#include "Unit/Character.h"
#include "ActModule.h"

void ActModule::operator()(cocos2d::Sprite & sp, ActData & act)
{
	//	当たり判定
	HitCheck()(sp, act);

	//	移動処理
	Jump()(sp, act);
	Move()(sp, act);
	Fall()(sp, act);

	//	アニメーションの更新
	AnimUpdate()(sp, act);
	//	向きの更新
	DirCheck()(sp, act);
}
