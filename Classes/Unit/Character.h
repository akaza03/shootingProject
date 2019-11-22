#pragma once
#include <functional>
#include "module/ActSet.h"
#include "Manager/AnimManager.h"
#include "Input/UseKey.h"
#include "Module/ActModule.h"
#include "Input/OprtState.h"

class OprtState;

//using spPointer = bool (*)(cocos2d::Sprite);
using actionPoint = std::function<bool(cocos2d::Sprite&,struct ActData&)>;
using keyList = std::map<UseKey, std::pair<bool, bool>>;							//	キー用のリスト(押されているかの判定,登録されているかの判定)
using hitList = std::map<DIR, bool>;												//	当たり判定用リスト

//	キャラクターの情報用
struct ActData
{
	cocos2d::Vec2 speed;													//	移動スピード(歩き,ジャンプ)
	float Gravity = 0;														//	重力
	keyList key;															//	どのキーを押したら処理するのか(List)
	AnimState anim;															//	自身のアニメーション
	AnimState nowAnim = AnimState::IDLE;									//	現在のアニメーション
	DIR dir = DIR::LEFT;													//	現在の向き
	hitList checkPoint;														//	当たり判定用
	cocos2d::Vec2 distance = { 0,0 };										//	移動距離
	bool jumpFlag = false;													//	ジャンプ中かどうかのフラグ
	int jumpCnt = 1;														//	一度にジャンプができる回数
	int jumpMax;															//	ジャンプ回数リセット用
	CharaType cType;														//	キャラクターのタイプ
};

class Character
	:public cocos2d::Sprite
{
public:
	Character();
	virtual ~Character();
	virtual void update(float d) = 0;

	void SetInit(std::string ImagePass, DIR stdir, cocos2d::Vec2 pos, cocos2d::Vec2 speed, cocos2d::Scene *scene);

	void SetDBBox(Sprite* sp);														//	デバッグ時の当たり判定用BoxのSet

private:
	void InitActData(cocos2d::Vec2 speed);											//	ActDataの初期化

protected:
	OprtState *_oprtState;															//	操作制御
	ActData _actData;																//	キャラクターの情報用
	std::map<const char *,ActData> _charaList;										//	キャラクターの情報用リスト

	Sprite *_box;																	//	当たり判定用のBOX

	//std::list<cocos2d::EventKeyboard::KeyCode> _keyList;							//	キー用のリスト

	//std::list<actionPoint> _actList;												//	アクションの管理用

	//bool(*_act)(cocos2d::Sprite&, ActData &);										//	関数ポインタ
};
