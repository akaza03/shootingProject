#pragma once
#include <functional>
#include "Manager/ResourceManager.h"
#include "Module/ActSet.h"
#include "Manager/AnimManager.h"
#include "Input/UseKey.h"
#include "Module/ActModule.h"
#include "Input/OprtState.h"
#include "Manager/AudioManager.h"
#include "Manager/EffManager.h"

class OprtState;

//using spPointer = bool (*)(cocos2d::Sprite);
using actionPoint = std::function<bool(cocos2d::Sprite&,struct ActData&)>;

using hitList = std::map<DIR, bool>;												//	当たり判定用リスト

using AnimMap = std::map < std::string, cocos2d::Action* >;							//	アニメーション格納用リスト
using changeList = std::vector<int>;												//	キャラチェンジ時のカウント用リスト

//	現在のキー,1フレーム前のキー,登録されているかどうか
using keyList = std::map<UseKey, std::tuple<bool, bool, bool>>;						//	キー用のリスト

//	キャラクターの情報用
struct ActData
{
	int HP = 10;															//	体力
	cocos2d::Vec2 speed;													//	移動スピード(歩き,ジャンプ)
	float Gravity = 0;														//	重力
	keyList key;															//	どのキーを押したら処理するのか(List)
	AnimState anim;															//	自身のアニメーション
	AnimState nowAnim = AnimState::IDLE;									//	現在のアニメーション
	DIR dir = DIR::LEFT;													//	現在の向き
	hitList checkPoint;														//	障害物との当たり判定用
	int damageCnt = 0;														//	ダメージを受けた時の硬直用
	int invTime = 0;														//	無敵時間
	cocos2d::Vec2 distance = { 0,0 };										//	移動距離
	bool jumpFlag = false;													//	ジャンプ中かどうかのフラグ
	int jumpCnt = 1;														//	一度にジャンプができる回数
	int jumpMax;															//	ジャンプ回数リセット用
	int attackCnt = 0;														//	攻撃してからの経過時間(Shot制御などで使用)
	CharaType cType;														//	キャラクターのタイプ
	int charaID;															//	キャラクターの種類判別用のID
	changeList changeCnt;													//	キャラチェンジ時のカウント用リスト
	cocos2d::Vec2 touchPos;													//	キャラチェンジ時等のタッチ座標
};

class Character
	:public cocos2d::Sprite
{
public:
	Character();
	virtual ~Character();
	virtual void update(float d) = 0;

	void SetInit(DIR stdir, int id, cocos2d::Vec2 pos, cocos2d::Vec2 speed, cocos2d::Scene *scene);

	void SetDBBox(Sprite* sp);														//	デバッグ時の当たり判定用BoxのSet

private:
	void InitActData(cocos2d::Vec2 speed);											//	ActDataの初期化

protected:
	OprtState *_oprtState;															//	操作制御
	ActData _actData;																//	キャラクターの情報用
	std::map<const char *,ActData> _charaList;										//	キャラクターの情報用リスト

	cocos2d::Vec2 oldTouchPos;

	Sprite *_box;																	//	当たり判定用のBOX

	AnimMap _animMap;

	//std::list<cocos2d::EventKeyboard::KeyCode> _keyList;							//	キー用のリスト

	//std::list<actionPoint> _actList;												//	アクションの管理用

	//bool(*_act)(cocos2d::Sprite&, ActData &);										//	関数ポインタ
};
