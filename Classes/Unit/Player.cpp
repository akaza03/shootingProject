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
	for (auto &itr : _charaList)
	{
		if (itr.second.nowAnim == itr.second.anim)
		{
			//	キーのチェック
			for (auto checkKey : _oprtState->GetKeyList())
			{
				//	そのキーが登録されていればキーを更新する
				if (itr.second.key[checkKey.first].second)
				{
					itr.second.key[checkKey.first].first = checkKey.second;
				}
			}

			//	当たり判定
			HitCheck()(*this, itr.second);

			//	移動処理
			Jump()(*this, itr.second);
			Move()(*this, itr.second);

			//	重力を加算する
			float gy = -0.05f;
			_Gravity += gy;
			//	足場がある場合は重力を0に
			if (itr.second.checkPoint[DIR::DOWN])
			{
				_Gravity = 0;
			}

			//	アニメーションの更新
			itr.second.nowAnim = lpAnimManager.AnimStateUpdate(itr.second);

			//	移動
			setPosition(getPosition().x + itr.second.distance.x, getPosition().y + itr.second.distance.y + _Gravity);

			//	向きの更新
			DirCheck()(*this, itr.second);

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

				lpAnimManager.AnimRun(this, itr.second.nowAnim, itr.second.cType);
			}
		}
	}
}

