#include "Player.h"

Player::Player()
{
	_actData.cType = CharaType::PLAYER;
	
	//this->scheduleUpdate();
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
			if (itr.second.anim == AnimState::THROW)
			{
				int a = 0;
			}

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

			if ((CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_MAC) && (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX))
			{
				std::get<0>(itr.second.key[UseKey::K_SPACE]) = true;
			}

			//	タッチ座標の取得
			if (_oprtState->GetTouchPoint() != oldTouchPos)
			{
				itr.second.touchPos = _oprtState->GetTouchPoint();
				oldTouchPos = itr.second.touchPos;
			}
			else
			{
				itr.second.touchPos = cocos2d::Vec2(-10, -10);
			}

			//	現在のHP
			auto oldHp = itr.second.HP;
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
				itr.second.HP = 0;
				itr.second.nowAnim = AnimState::DIE;
			}

			if (itr.second.HP >= itr.second.MaxHP)
			{
				itr.second.HP = itr.second.MaxHP;
			}

			//	HPバーの増減
			if (oldHp != itr.second.HP)
			{
				auto layer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("UILayer");
				cocos2d::Sprite* HPBar = (cocos2d::Sprite*) layer->getChildByName("hpBar");
				//	最大HPから見た現在のHPの割合
				float HPPercent = (float)itr.second.HP / (float)itr.second.MaxHP;
				//	一旦戻す
				auto oldSize = HPBar->getScaleX();
				float ImageSizeX = HPBar->getContentSize().width * (1 - oldSize);
				HPBar->setPosition(HPBar->getPosition().x + ImageSizeX / 2, HPBar->getPosition().y);

				//	HPバーの拡大縮小(X座標のみ)
				HPBar->setScale(HPPercent, 1);
				//	増減した分の位置補正
				ImageSizeX = HPBar->getContentSize().width * (1 - HPPercent);
				HPBar->setPosition(HPBar->getPosition().x - ImageSizeX / 2, HPBar->getPosition().y);
			}

			if (itr.second.HP <= 0 && oldHp != itr.second.HP)
			{
				lpEffectManager.SetEffect(RES_ID("deathEff").c_str(), "FGLayer", true, getPosition(), 20, true);
				lpAudioManager.SetSound("shot");
				itr.second.nowAnim = AnimState::DIE;
				_actData.nowAnim = AnimState::DIE;
			}

			//	外部のチェック用
			_actData.nowAnim = itr.second.nowAnim;
			_actData.damageCnt = itr.second.damageCnt;

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
				nextKey.damageNumber = itr.second.damageNumber;
				nextKey.dirInver = itr.second.dirInver;
				nextKey.changeCnt = itr.second.changeCnt;
				nextKey.charaID = itr.second.charaID;
				nextKey.touchPos = itr.second.touchPos;

				lpAnimMng.AnimRun(this, itr.second.nowAnim, itr.second.cType, _animMap);
			}
		}
	}
}

