#pragma once
#include <cocos2d.h>

class Shot
	:public cocos2d::Sprite
{
public:
	Shot();
	~Shot();
	//	画像パス,発射キャラのスプライト,発射キャラの情報,弾の攻撃力,弾のスピード
	void SetInit(std::string ImagePass, cocos2d::Sprite & sp, ActData &chara, float sPower, float sSpeed);
	void update(float d);
	CharaType GetType();
	float GetPower();
	bool GetAtkFlag();
	CREATE_FUNC(Shot);

private:
	float power = 0;						//	弾の攻撃力
	float speed = 0;						//	弾のスピード
	CharaType type;							//	だれが撃った弾か
	int charaID;
	bool atkFlag;							//	攻撃判定があるかどうか
	float distance = 0;						//	移動した距離
	bool hitChara;							//	キャラとの当たり判定
	bool hitObj;							//	地形との当たり判定

	void TypeInit(ActData &chara);			//	charaTypeごとのInit処理
	void TypeUpdate();						//	charaTypeごとのupdate処理
	void HitCheck();
};

