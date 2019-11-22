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
	_animMap["p_run"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(2, 1), 2, 0.3f, true);
	_animMap["p_runShot"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(1, 3), 5, 0.3f, true);
	_animMap["p_jump"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 5), 3, 0.3f, true);
	_animMap["p_damage"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 4), 3, 0.3f, true);
	_animMap["p_die"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(6, 5), 3, 0.3f, true);

	pass = "image/Sprites/enemies/";
}

cocos2d::Action * AnimManager::AnimationCreate(std::string imagePass, cocos2d::Vec2 divCnt, cocos2d::Vec2 startID, int animCntMax, float frame, bool loop)
{
	//	キャッシュ用画像
	auto cacheSp = cocos2d::Sprite::create(imagePass);
	auto spTexture = cacheSp->getTexture();
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
	_animMap["p_run"]->retain();
	_animMap["p_runShot"]->retain();
	_animMap["p_jump"]->retain();
	_animMap["p_damage"]->retain();
	_animMap["p_die"]->retain();
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
		case JUMP:
			return "p_jump";
			break;
		case DAMAGE:
			return "p_damage";
			break;
		case DIE:
			return "p_die";
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
		case JUMP:
			break;
		case DAMAGE:
			break;
		case DIE:
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
	return "non";
}
