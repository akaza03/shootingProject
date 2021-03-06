#include "Unit/Character.h"
#include "ActModule.h"

void ActModule::operator()(cocos2d::Sprite & sp, ActData & act)
{
	//	移動処理
	Jump()(sp, act);
	Move()(sp, act);
	Fall()(sp, act);

	//	アニメーションの更新
	AnimUpdate()(sp, act);
	//	向きの更新
	DirCheck()(sp, act);
	//	移動
	SetPos()(sp, act);

	//	弾発射
	Shooting()(sp, act);

	//	キャラクターの切り替え
	changeChara()(sp, act);

	//	キーの更新
	OldKeyUpdate()(sp, act);

	//	当たり判定
	HitCheck()(sp, act);
	DamageCheck()(sp, act);
}
