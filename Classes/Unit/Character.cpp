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


bool Character::SetInit(DIR stdir, int id, cocos2d::Vec2 pos, int hp, cocos2d::Vec2 speed,
							cocos2d::Scene *scene, float disAtk, cocos2d::Vec2 disDir, bool armor)
{
	_actData.charaID = id;
	_actData.HP = hp;
	_actData.MaxHP = hp;
	_actData.searchDisAtk = disAtk;
	_actData.searchDisDir = disDir;
	_actData.superArmor = armor;

	//	アニメーションのセット
	if (!lpAnimMng.SetAnim(_actData.cType, id, _animMap))
	{
		return false;
	}

	InitActData(speed);

	auto sprite = Sprite::create();
	setPosition(cocos2d::Vec2(pos.x + sprite->getContentSize().width / 2, pos.y));

	if (_actData.cType == CharaType::PLAYER)
	{
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
		scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_oprtState->oprtInit(), scene);
	}

	setFlippedX(true);
	return true;
}

void Character::InitActData(cocos2d::Vec2 speed)
{
	//	キャラクターの情報の追加
	_actData.jumpMax = _actData.jumpCnt;
	_actData.speed = speed;
	_actData.touchPos = cocos2d::Vec2(-10, -10);
	oldTouchPos = _actData.touchPos;

	for (int i = 0 ; i < 3 ; i++)
	{
		_actData.changeCnt.push_back(0);
	}
	
	_actData.key[UseKey::K_LEFT] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_RIGHT] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_UP] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_DOWN] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_SPACE] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_A] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_S] = std::make_tuple(false, false, true);

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
	std::get<2>(_actData.key[UseKey::K_DOWN]) = false;
	_charaList.emplace(std::make_pair("jump", _actData));

	_actData.key[UseKey::K_LEFT] = std::make_tuple(false, false, false);
	_actData.key[UseKey::K_RIGHT] = std::make_tuple(false, false, false);
	_actData.key[UseKey::K_UP] = std::make_tuple(false, false, false);
	_actData.key[UseKey::K_DOWN] = std::make_tuple(false, false, false);
	_actData.key[UseKey::K_SPACE] = std::make_tuple(false, false, false);
	_actData.key[UseKey::K_A] = std::make_tuple(false, false, false);
	_actData.key[UseKey::K_S] = std::make_tuple(false, false, false);

	_actData.anim = AnimState::DAMAGE;
	_charaList.emplace(std::make_pair("damage", _actData));
	_actData.anim = AnimState::THROW;
	_charaList.emplace(std::make_pair("throw", _actData));
	_actData.anim = AnimState::DIE;
	_charaList.emplace(std::make_pair("die", _actData));

	lpAnimMng.AnimRun(this, _charaList["idle"].nowAnim, _charaList["idle"].cType, _animMap);
}


AnimState Character::CheckAnim()
{
	return _actData.nowAnim;
}
