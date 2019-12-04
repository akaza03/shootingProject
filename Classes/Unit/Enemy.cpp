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
	for (auto &itr : _charaList)
	{
		if (itr.second.nowAnim == itr.second.anim)
		{
			//	���W���[�����g�p�����A�N�V��������
			ActModule()(*this, itr.second);

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
					nextKey.key[itrKey].first = itr.second.key[itrKey].first;
					//	���̃A�j���[�V�����̃L�[����������
					itr.second.key[itrKey].first = false;
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

				lpAnimManager.AnimRun(this, itr.second.nowAnim, itr.second.cType, _animMap);
			}
		}
	}
}

void Enemy::AnimStateUpdate()
{

}
