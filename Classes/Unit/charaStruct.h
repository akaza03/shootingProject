#pragma once

//	アニメーションのタイプ
enum AnimState
{
	IDLE,
	RUN,
	RSHOT,
	JUMP,
	DAMAGE,
	DIE,
	STATE_MAX
};

//	キャラクターのタイプ
enum CharaType
{
	PLAYER,
	ENEMY,
	CHARA_MAX
};

//	向き
enum DIR
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	DIR_MAX
};
