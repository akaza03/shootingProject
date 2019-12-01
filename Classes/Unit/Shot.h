#pragma once
#include <cocos2d.h>

class Shot
	:public cocos2d::Sprite
{
public:
	Shot();
	~Shot();
	//	画像パス,発射キャラのスプライト,発射キャラの情報
	void SetInit(std::string ImagePass, cocos2d::Sprite & sp, ActData &chara);
	void update(float d);
	CREATE_FUNC(Shot);

private:
	float speed = 0;						//	弾のスピード
	CharaType type;							//	だれが撃った弾か
	float distance = 0;						//	移動した距離

	bool hitCheck();
};

