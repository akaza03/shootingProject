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
			//	モジュールを使用したアクション処理
			ActModule()(*this, itr.second);

			if (itr.second.nowAnim != itr.second.anim)
			{
				//	次のアニメーションに現在のキー情報を渡す準備
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

				//	キーの初期化
				for (auto itrKey : UseKey())
				{
					//	次のアニメーションに現在のアニメーションのキー情報を渡す
					nextKey.key[itrKey].first = itr.second.key[itrKey].first;
					//	今のアニメーションのキー情報を初期化
					itr.second.key[itrKey].first = false;
				}
				//	次のアニメーションに現在のアニメーションと向きを渡す
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
