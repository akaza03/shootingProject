#include "Enemy.h"



Enemy::Enemy()
{
	//Sprite::create("image/Sprites/enemies/crab-idle/crab-idle-1.png");
	//setPosition(cocos2d::Vec2(100, 100));

	_actData.cType = CharaType::ENEMY;

	this->scheduleUpdate();
}


Enemy::~Enemy()
{
}

void Enemy::update(float d)
{
	auto deathFlag = false;
	for (auto &itr : _charaList)
	{
		if (itr.second.nowAnim == itr.second.anim)
		{
			objTurn(itr.second);

			//	���W���[�����g�p�����A�N�V��������
			ActModule()(*this, itr.second);

			if (itr.second.HP <= 0)
			{
				deathFlag = true;
			}

			if (itr.second.nowAnim != itr.second.anim)
			{
				//	���̃A�j���[�V�����Ɍ��݂̃L�[����n������
				char* nextKeyName = "idle";
				switch (itr.second.nowAnim)
				{
				case IDLE:
					nextKeyName = "idle";
					break;
				case RUN:
					nextKeyName = "run";
					break;
				case RSHOT:
					nextKeyName = "pShot";
					break;
				case JUMP:
					nextKeyName = "jump";
					break;
				case DAMAGE:
					nextKeyName = "damage";
					break;
				case THROW:
					nextKeyName = "throw";
					break;
				case DIE:
					nextKeyName = "die";
					break;
				case STATE_MAX:
					break;
				default:
					break;
				}
				auto &nextKey = _charaList[nextKeyName];

				//	�L�[�̏�����
				for (auto itrKey : UseKey())
				{
					//	���̃A�j���[�V�����Ɍ��݂̃A�j���[�V�����̃L�[����n��
					std::get<0>(nextKey.key[itrKey]) = std::get<0>(itr.second.key[itrKey]);
					std::get<1>(nextKey.key[itrKey]) = std::get<1>(itr.second.key[itrKey]);
					//	���̃A�j���[�V�����̃L�[����������
					std::get<0>(itr.second.key[itrKey]) = false;
					std::get<1>(itr.second.key[itrKey]) = false;
				}
				//	���̃A�j���[�V�����Ɍ��݂̃A�j���[�V�����ƌ�����n��
				nextKey.nowAnim = itr.second.nowAnim;
				nextKey.dir = itr.second.dir;
				nextKey.Gravity = itr.second.Gravity;
				nextKey.jumpFlag = itr.second.jumpFlag;
				nextKey.jumpCnt = itr.second.jumpCnt;
				nextKey.attackCnt = itr.second.attackCnt;
				nextKey.damageCnt = itr.second.damageCnt;
				nextKey.invTime = itr.second.invTime;
				nextKey.HP = itr.second.HP;
				nextKey.damageNumber = itr.second.damageNumber;
				nextKey.dirInver = itr.second.dirInver;

				lpAnimMng.AnimRun(this, itr.second.nowAnim, itr.second.cType, _animMap);
			}
		}
	}

	if (deathFlag)
	{
		lpEffectManager.SetEffect(RES_ID("deathEff").c_str(), "FGLayer", true, getPosition(), 20, true);
		lpAudioManager.SetSound("shot");
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		auto layer = nowScene->getChildByName("EMLayer");
		layer->removeChild(this);
	}
}

bool Enemy::playerSearch(ActData &act)
{
	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();

	auto player = nowScene->getChildByName("PLLayer")->getChildByName("player");

	if (player)
	{
		//	�v���C���[�Ƃ̋���
		auto distance = getPosition() - player->getPosition();

		//	�v���C���[�̏ꏊ�ɂ���Č�����ς���
		if (act.dirFixed)
		{
			if (abs(distance.x) < act.searchDisDir.x && abs(distance.y) < act.searchDisDir.y && (act.checkPoint[DIR::DOWN] == true))
			{
				if (distance.x > 0)
				{
					act.dir = DIR::LEFT;
				}
				else if (distance.x < 0)
				{
					act.dir = DIR::RIGHT;
				}
			}
		}

		auto a = getContentSize();

		//	���̋����ɓ�������U��
		if (abs(distance.x) < act.searchDisAtk && abs(distance.y) < act.searchDisDir.y)
		{
			std::get<0>(act.key[UseKey::K_SPACE]) = true;
			std::get<0>(act.key[UseKey::K_RIGHT]) = false;
			std::get<0>(act.key[UseKey::K_LEFT]) = false;
		}
		else
		{
			std::get<0>(act.key[UseKey::K_SPACE]) = false;

			//	�ړ�����
			if (act.dir == DIR::LEFT)
			{
				std::get<0>(act.key[UseKey::K_LEFT]) = true;
				std::get<0>(act.key[UseKey::K_RIGHT]) = false;
			}
			if (act.dir == DIR::RIGHT)
			{
				std::get<0>(act.key[UseKey::K_RIGHT]) = true;
				std::get<0>(act.key[UseKey::K_LEFT]) = false;
			}
		}
	}

	return false;
}

void Enemy::objTurn(ActData &act)
{
	auto oldDir = act.dir;
	if (act.dirFixed)
	{
		if ((act.dir == DIR::LEFT) && ((act.checkPoint[DIR::LEFT] == true) || (act.checkPoint[DIR::DOWN] == false)))
		{
			act.dir = DIR::RIGHT;
		}
		else if ((act.dir == DIR::RIGHT) && ((act.checkPoint[DIR::RIGHT] == true) || (act.checkPoint[DIR::DOWN] == false)))
		{
			act.dir = DIR::LEFT;
		}
	}

	playerSearch(act);

	if (oldDir != act.dir)
	{
		if (act.dir == DIR::RIGHT)
		{
			this->setFlippedX(true);
		}
		else if (act.dir == DIR::LEFT)
		{
			this->setFlippedX(false);
		}
	}
}

void Enemy::typeUpdate(ActData & act)
{

}
