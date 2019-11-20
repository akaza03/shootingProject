#pragma once

//	アニメーションのタイプ
enum AnimState
{
	IDLE,
	RUN,
	RSHOT,
	SHOTUP,
	STAND,
	JUMP,
	CLING,
	DUCK,
	HURT,
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
