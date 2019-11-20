#include "Unit/Character.h"
#include "AnimManager.h"

AnimManager* AnimManager::s_Instance = nullptr;

AnimManager::AnimManager()
{
	AnimationInit();
}


AnimManager::~AnimManager()
{

}

void AnimManager::AnimationInit()
{
	auto pass = "image/player/01-unit.png";
	_animMap["p_idle"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 0), 3, 0.3f, true);
	//_animMap["p_run"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 5), 3, 0.1f, true);

	//_animMap["p_idle"] = AnimationCreate(pass, 3, 0.5f, "player-idle-%i.png", true);
	//_animMap["p_run"] = AnimationCreate(pass, 3, 0.1f, "player-run-%i.png", true);
	//_animMap["p_runShot"] = AnimationCreate(pass, 3, 0.3f, "player-run-shot-%i.png", true);
	//_animMap["p_shotUp"] = AnimationCreate(pass, 3, 1, "player-shoot-up-%i.png", true);
	//_animMap["p_stand"] = AnimationCreate(pass, 3, 0.5f, "player-stand-%i.png", true);
	//_animMap["p_jump"] = AnimationCreate(pass, 6, 0.5f, "player-jump-%i.png", true);
	//_animMap["p_cling"] = AnimationCreate(pass, 3, 1, "player-cling-%i.png", true);
	//_animMap["p_duck"] = AnimationCreate(pass, 3, 1, "player-duck-%i.png", true);
	//_animMap["p_hurt"] = AnimationCreate(pass, 3, 1.0f, "player-hurt-%i.png", true);

	pass = "image/Sprites/enemies/";
}

cocos2d::Action * AnimManager::AnimationCreate(std::string imagePass, cocos2d::Vec2 divCnt, cocos2d::Vec2 startID, int animCntMax, float frame, bool loop)
{
	//	キャッシュ用画像
	auto cacheSp = cocos2d::Sprite::create(imagePass);
	auto spTexture = cacheSp->getTexture();
	auto cache = cocos2d::SpriteFrameCache::getInstance();
	auto _animation = cocos2d::Animation::create();
	//	1コマのサイズ
	auto imageSize = cocos2d::Vec2(cacheSp->getContentSize().width / divCnt.x, cacheSp->getContentSize().height / divCnt.y);

	for (int i = 0; i < animCntMax; i++)
	{
		if (startID.x >= divCnt.x)
		{
			startID.x = 0;
			startID.y++;
		}
		_animation->addSpriteFrameWithTexture(spTexture,cocos2d::Rect(startID.x * imageSize.x, startID.y * imageSize.y,
																		imageSize.x, imageSize.y));
		//_animation->addSpriteFrameWithTexture(spTexture, cocos2d::Rect(0,0,imageSize.x,imageSize.y));
		startID.x++;
	}

	_animation->setDelayPerUnit(frame);
	_animation->setRestoreOriginalFrame(true);

	auto animate = cocos2d::Animate::create(_animation);

	//	ループするかどうかの処理
	if (loop)
	{
		return cocos2d::RepeatForever::create(animate);
	}
	return animate;
}

void AnimManager::AnimRun(cocos2d::Sprite * sprite, AnimState anim, CharaType type)
{
	auto animName = GetAnimName(anim, type);

	auto action = _animMap[animName];
	if (action != nullptr)
	{
		sprite->stopAllActions();
		sprite->runAction(_animMap[animName]);
	}
	AnimCountPlus();
}

AnimState AnimManager::AnimStateUpdate(struct ActData &act)
{
	if (act.distance.y != 0)
	{
		return AnimState::JUMP;
	}
	else if (act.distance.x != 0)
	{
		return AnimState::RUN;
	}
	else
	{
		return AnimState::IDLE;
	}
	return AnimState::IDLE;
}

void AnimManager::AnimCountPlus()
{
	_animMap["p_idle"]->retain();
	//_animMap["p_run"]->retain();
	//_animMap["p_runShot"]->retain();
	//_animMap["p_shotUp"]->retain();
	//_animMap["p_stand"]->retain();
	//_animMap["p_jump"]->retain();
	//_animMap["p_cling"]->retain();
	//_animMap["p_duck"]->retain();
	//_animMap["p_hurt"]->retain();
}

std::string AnimManager::GetAnimName(AnimState anim, CharaType type)
{
	switch (type)
	{
	case CharaType::PLAYER:
		switch (anim)
		{
		case IDLE:
			return "p_idle";
			break;
		case RUN:
			return "p_run";
			break;
		case RSHOT:
			return "p_runShot";
			break;
		case SHOTUP:
			return "p_shotUp";
			break;
		case STAND:
			return "p_stand";
			break;
		case JUMP:
			return "p_jump";
			break;
		case CLING:
			return "p_cling";
			break;
		case DUCK:
			return "p_duck";
			break;
		case HURT:
			return "p_hurt";
			break;
		case STATE_MAX:
			break;
		default:
			break;
		}
		break;
	case CharaType::ENEMY:
		switch (anim)
		{
		case IDLE:
			break;
		case RUN:
			break;
		case RSHOT:
			break;
		case SHOTUP:
			break;
		case STAND:
			break;
		case JUMP:
			break;
		case CLING:
			break;
		case DUCK:
			break;
		case HURT:
			break;
		case STATE_MAX:
			break;
		default:
			break;
		}
		break;
	case CharaType::CHARA_MAX:
		break;
	default:
		break;
	}
	return "なし";
}
