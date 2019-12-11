#include "Player.h"

Player::Player()
{
	_actData.cType = CharaType::PLAYER;
	
	this->scheduleUpdate();
}

Player::~Player()
{
}

void Player::update(float d)
{
	auto deathFlag = false;
	for (auto &itr : _charaList)
	{
		if (itr.second.nowAnim == itr.second.anim)
		{
			//	キーのチェック
			for (auto checkKey : _oprtState->GetKeyList())
			{
				//	そのキーが登録されていればキーを更新する
				if (std::get<2>(itr.second.key[checkKey.first]))
				{
					//itr.second.key[checkKey.first].first = checkKey.second;
					std::get<0>(itr.second.key[checkKey.first]) = checkKey.second;
				}
			}

			//	現在のcharaID
			auto oldID = itr.second.charaID;

			//	モジュールを使用したアクション処理
			ActModule()(*this, itr.second);

			//	キャラクターの交代
			if (oldID != itr.second.charaID)
			{
				_animMap.clear();
				lpAnimMng.SetAnim(itr.second.cType, itr.second.charaID, _animMap);
				lpAnimMng.AnimRun(this, itr.second.nowAnim, itr.second.cType, _animMap);
			}

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
				//	ステータスを渡す
				nextKey.nowAnim = itr.second.nowAnim;
				nextKey.dir = itr.second.dir;
				nextKey.Gravity = itr.second.Gravity;
				nextKey.jumpFlag = itr.second.jumpFlag;
				nextKey.jumpCnt = itr.second.jumpCnt;
				nextKey.attackCnt = itr.second.attackCnt;
				nextKey.damageCnt = itr.second.damageCnt;
				nextKey.invTime = itr.second.invTime;
				nextKey.HP = itr.second.HP;
				nextKey.changeCnt = itr.second.changeCnt;
				nextKey.charaID = itr.second.charaID;

				lpAnimMng.AnimRun(this, itr.second.nowAnim, itr.second.cType, _animMap);
			}
		}
	}

	if (deathFlag)
	{
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		auto layer = nowScene->getChildByName("PLLayer");
		layer->removeChild(this);
	}
}

