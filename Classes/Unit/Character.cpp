#include "Input/OprtKey.h"
#include "Input/OprtTouch.h"
#include "_DebugOut/_DebugConOut.h"
#include "Character.h"

Character::Character()
{
}


Character::~Character()
{
}


void Character::SetInit(std::string ImagePass, DIR stdir, cocos2d::Vec2 pos, cocos2d::Vec2 speed, cocos2d::Scene *scene)
{
	InitActData(speed);
	auto sprite = Sprite::create(ImagePass);
	setPosition(cocos2d::Vec2(pos.x + sprite->getContentSize().width / 2, pos.y));

	//	プラットフォームによって操作方法を変える
	if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
	{
		_oprtState = new OprtKey();
	}
	else
	{
		_oprtState = new OprtTouch();
	}
	//	操作イベントの作成
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_oprtState->oprtInit(this),scene);
}

void Character::InitActData(cocos2d::Vec2 speed)
{
	//	キャラクターの情報の追加
	_actData.jumpMax = _actData.jumpCnt;
	_actData.speed = speed;
	_actData.key[UseKey::K_LEFT] = std::make_pair(false, true);
	_actData.key[UseKey::K_RIGHT] = std::make_pair(false, true);
	_actData.key[UseKey::K_UP] = std::make_pair(false, true);
	_actData.key[UseKey::K_DOWN] = std::make_pair(false, true);
	_actData.key[UseKey::K_SPACE] = std::make_pair(false, true);

	_actData.checkPoint[DIR::LEFT] = false;
	_actData.checkPoint[DIR::RIGHT] = false;
	_actData.checkPoint[DIR::UP] = false;
	_actData.checkPoint[DIR::DOWN] = false;

	_actData.anim = AnimState::IDLE;
	_charaList.emplace(std::make_pair("idle", _actData));
	_actData.anim = AnimState::RUN;
	_charaList.emplace(std::make_pair("run", _actData));
	_actData.anim = AnimState::RSHOT;
	_charaList.emplace(std::make_pair("pShot", _actData));
	_actData.anim = AnimState::JUMP;
	_actData.key[UseKey::K_DOWN].second = false;
	_charaList.emplace(std::make_pair("jump", _actData));
	_actData.anim = AnimState::DAMAGE;
	_charaList.emplace(std::make_pair("damage", _actData));
	_actData.anim = AnimState::DIE;
	_charaList.emplace(std::make_pair("die", _actData));

	lpAnimManager.AnimRun(this, _charaList["idle"].nowAnim, _charaList["idle"].cType);
}

void Character::SetDBBox(Sprite * sp)
{
#ifdef _DEBUG
	//	当たり判定用の四角描画
	_box = sp;
#endif // _DEBUG
}
