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
	_animMap["p0_idle"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 0), 3, 0.3f, true);
	_animMap["p0_run"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(2, 1), 2, 0.3f, true);
	_animMap["p0_runShot"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(1, 3), 5, 0.3f, true);
	_animMap["p0_jump"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 5), 3, 0.3f, true);
	_animMap["p0_damage"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 4), 3, 0.3f, true);
	_animMap["p0_die"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(6, 5), 3, 0.3f, true);

	pass = "image/player/02-unit.png";
	_animMap["e0_idle"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 0), 3, 0.3f, true);
	_animMap["e0_run"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(2, 1), 2, 0.3f, true);
	_animMap["e0_runShot"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(1, 3), 5, 0.3f, true);
	_animMap["e0_jump"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 5), 3, 0.3f, true);
	_animMap["e0_damage"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 4), 3, 0.3f, true);
	_animMap["e0_die"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(6, 5), 3, 0.3f, true);
}

cocos2d::Animation * AnimManager::AnimationCreate(std::string imagePass, cocos2d::Vec2 divCnt, cocos2d::Vec2 startID, int animCntMax, float frame, bool loop)
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

	return _animation;

	//auto animate = cocos2d::Animate::create(_animation);
	////	ループするかどうかの処理
	//if (loop)
	//{
	//	return cocos2d::RepeatForever::create(animate);
	//}
	//return animate;
}

void AnimManager::AnimRun(cocos2d::Sprite * sprite, AnimState anim, CharaType type , AnimMap &charaAnim)
{
	auto animName = GetAnimName(anim);

	auto action = charaAnim[animName];

	if (action != nullptr)
	{
		sprite->stopAllActions();
		sprite->runAction(charaAnim[animName]);
	}
	AnimCountPlus(charaAnim);
}


void AnimManager::SetAnim(CharaType type, int id, AnimMap &anim)
{
	std::string charaID;
	if (type == CharaType::PLAYER)
	{
		charaID = "p";
	}
	else if (type == CharaType::ENEMY)
	{
		charaID = "e";
	}

	charaID = charaID + std::to_string(id);

	anim["idle"]	= cocos2d::RepeatForever::create(cocos2d::Animate::create(_animMap[charaID + "_idle"]));
	anim["run"]		= cocos2d::RepeatForever::create(cocos2d::Animate::create(_animMap[charaID + "_run"]));
	anim["runShot"] = cocos2d::RepeatForever::create(cocos2d::Animate::create(_animMap[charaID + "_runShot"]));
	anim["jump"]	= cocos2d::RepeatForever::create(cocos2d::Animate::create(_animMap[charaID + "_jump"]));
	anim["damage"]	= cocos2d::RepeatForever::create(cocos2d::Animate::create(_animMap[charaID + "_damage"]));
	anim["die"]		= cocos2d::RepeatForever::create(cocos2d::Animate::create(_animMap[charaID + "_die"]));
}

void AnimManager::AnimCountPlus(AnimMap &anim)
{
	anim["idle"]->retain();
	anim["run"]->retain();
	anim["runShot"]->retain();
	anim["jump"]->retain();
	anim["damage"]->retain();
	anim["die"]->retain();
}

std::string AnimManager::GetAnimName(AnimState anim)
{
	switch (anim)
	{
	case IDLE:
		return "idle";
		break;
	case RUN:
		return "run";
		break;
	case RSHOT:
		return "runShot";
		break;
	case JUMP:
		return "jump";
		break;
	case DAMAGE:
		return "damage";
		break;
	case DIE:
		return "die";
		break;
	case STATE_MAX:
		break;
	default:
		break;
	}
	return "non";
}
