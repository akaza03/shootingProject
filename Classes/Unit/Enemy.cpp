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

			//	�ړ�����
			if (itr.second.dir == DIR::LEFT)
			{
				std::get<0>(itr.second.key[UseKey::K_LEFT]) = true;
			}
			if(itr.second.dir == DIR::RIGHT)
			{
				std::get<0>(itr.second.key[UseKey::K_RIGHT]) = true;
			}

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

				lpAnimMng.AnimRun(this, itr.second.nowAnim, itr.second.cType, _animMap);
			}
		}
	}

	if (deathFlag)
	{
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		auto layer = nowScene->getChildByName("EMLayer");
		layer->removeChild(this);
	}
}

bool Enemy::playerSearch(ActData act)
{
	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();

	auto layer = nowScene->getChildByName("PLLayer");



	//if (act.dir == )
	//{

	//}
	return false;
}

void Enemy::objTurn(ActData &act)
{
	auto oldDir = act.dir;
	if ((act.dir == DIR::LEFT) && (act.checkPoint[DIR::LEFT] == true))
	{
		act.dir = DIR::RIGHT;
	}
	else if ((act.dir == DIR::RIGHT) && (act.checkPoint[DIR::RIGHT] == true))
	{
		act.dir = DIR::LEFT;
	}

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
