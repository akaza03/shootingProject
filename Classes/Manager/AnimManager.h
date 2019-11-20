#pragma once
#include <map>
#include "cocos2d.h"
#include "Unit/charaStruct.h"
#include "Unit/Character.h"

#define lpAnimManager AnimManager::GetInstance()

class Character;

class AnimManager
{
public:
	static AnimManager& GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new AnimManager();
		}
		return *s_Instance;
	}
	~AnimManager();

	//	アニメーションの登録
	//	画像パス,画像全体の分割数,分割開始ID,アニメーションの分割数,フレーム数
	cocos2d::Action* AnimationCreate(std::string imagePass, cocos2d::Vec2 divCnt, cocos2d::Vec2 startID, int animCntMax, float frame, bool loop);

	void AnimRun(cocos2d::Sprite* sprite, AnimState anim, CharaType type);		//	アニメーションの開始

	AnimState AnimStateUpdate(struct ActData &act);								//	ステートのアップデート
private:
	AnimManager();
	void AnimationInit();														//	アニメーションの登録用

	std::string GetAnimName(AnimState anim, CharaType type);					//	アニメーション開始時のアニメーション名取得用

	void AnimCountPlus();														//	参照カウントを増やす

	std::map < std::string, cocos2d::Action* > _animMap;						//	アニメーション情報を収納
	static AnimManager* s_Instance;
};
