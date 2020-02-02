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

			//	モジュールを使用したアクション処理
			ActModule()(*this, itr.second);

			if (itr.second.HP <= 0)
			{
				deathFlag = true;
			}

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

				//	キーの初期化
				for (auto itrKey : UseKey())
				{
					//	次のアニメーションに現在のアニメーションのキー情報を渡す
					std::get<0>(nextKey.key[itrKey]) = std::get<0>(itr.second.key[itrKey]);
					std::get<1>(nextKey.key[itrKey]) = std::get<1>(itr.second.key[itrKey]);
					//	今のアニメーションのキー情報を初期化
					std::get<0>(itr.second.key[itrKey]) = false;
					std::get<1>(itr.second.key[itrKey]) = false;
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
		//	プレイヤーとの距離
		auto distance = getPosition() - player->getPosition();

		//	プレイヤーの場所によって向きを変える
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

		//	一定の距離に入ったら攻撃
		if (abs(distance.x) < act.searchDisAtk && abs(distance.y) < act.searchDisDir.y)
		{
			std::get<0>(act.key[UseKey::K_SPACE]) = true;
			std::get<0>(act.key[UseKey::K_RIGHT]) = false;
			std::get<0>(act.key[UseKey::K_LEFT]) = false;
		}
		else
		{
			std::get<0>(act.key[UseKey::K_SPACE]) = false;

			//	移動処理
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
