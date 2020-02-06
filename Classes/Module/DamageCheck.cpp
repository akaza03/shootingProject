#include "Unit/Character.h"
#include "Unit/Shot.h"
#include "DamageCheck.h"

bool DamageCheck::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
	auto layer = nowScene->getChildByName("ATKLayer");

	auto charaBox = sp.boundingBox();
	//	攻撃レイヤーとの判定
	for (auto obj : layer->getChildren())
	{
		//	判定用BOX
		auto objBox = obj->boundingBox();

		Shot* shot = (Shot*)obj;
		if ((shot->GetType() == CharaType::PLAYER && act.cType == CharaType::ENEMY)
			|| (shot->GetType() == CharaType::ENEMY && act.cType == CharaType::PLAYER))
		{
			if (charaBox.intersectsRect(objBox) && shot->GetAtkFlag())
			{
				//	弾に消滅判定
				shot->SetHitChara(true);
				act.damageNumber = shot->GetPower();

				if (act.damageCnt <= 0 && act.invTime <= 0 && act.anim != AnimState::THROW && act.anim != AnimState::DAMAGE)
				{
					//	攻撃を受けた方向を向く
					if (shot->GetSpeed() >= 0)
					{
						if (act.dir != DIR::LEFT)
						{
							act.dirInver = true;
						}
					}
					else
					{
						if (act.dir != DIR::RIGHT)
						{
							act.dirInver = true;
						}
					}

					//	当たった場合はダメージ硬直
					act.damageCnt = shot->GetStunTime();
					if (shot->GetThrow())
					{
						act.nowAnim = AnimState::THROW;
					}
					else
					{
						DoDamage(sp, act);
					}
				}
			}
		}
	}

	if (act.anim == AnimState::THROW)
	{
		if (act.damageCnt == 0)
		{
			//	壁に接触した場合ダメージ処理に移る
			if (act.checkPoint[DIR::LEFT] || act.checkPoint[DIR::RIGHT])
			{
				DoDamage(sp, act);
				act.damageCnt = 50;
				act.nowAnim = AnimState::DAMAGE;
			}
			else
			{
				//	攻撃を受けた方向と逆の方向に吹っ飛ぶ
				float _speed = 0;
				if (act.dir == DIR::LEFT)
				{
					_speed = 10;
				}
				else
				{
					_speed = -10;
				}
				sp.setPosition(sp.getPosition().x + _speed, sp.getPosition().y);
			}
		}
		else
		{
			act.Gravity = 0;
			act.jumpFlag = false;
		}
	}

	if (act.damageCnt != 0)
	{
		act.damageCnt--;
		//	ダメージ硬直時キャラクターを揺らす
			if (act.damageCnt % 10 == 0)
			{
				sp.setPosition(sp.getPosition().x + 5, sp.getPosition().y);
			}
			else if(act.damageCnt % 10 == 5)
			{
				sp.setPosition(sp.getPosition().x - 5, sp.getPosition().y);
			}
	}

	if (act.anim == AnimState::DAMAGE)
	{
		//	ダメージ硬直が終わった瞬間に無敵を付与する
		if (act.damageCnt <= 0)
		{
			if (act.cType == CharaType::PLAYER)
			{
				act.invTime = 100;
			}
			sp.setOpacity(0);
		}
	}

	if (act.invTime > 0)
	{
		act.invTime--;
		//	無敵時の点滅用
		if (sp.getOpacity() == 0)
		{
			sp.setOpacity(255);
		}
		else
		{
			sp.setOpacity(0);
		}
	}
	else
	{
		sp.setOpacity(255);
	}

	//	ステージ外に出たら死亡
	if (sp.getPosition().y < -sp.getContentSize().height)
	{
		act.HP = 0;
	}

	//	HPが上限を超えないように
	if (act.HP > act.MaxHP)
	{
		act.HP = act.MaxHP;
	}

	return false;
}

void DamageCheck::DoDamage(cocos2d::Sprite & sp, ActData & act)
{
	//	ダメージ
	act.HP -= act.damageNumber;
	act.damageNumber = 0;
	if (act.HP > 0)
	{
		lpAudioManager.SetSound("damage");
		lpEffectManager.SetEffect((RES_ID("hitEff").c_str()), "FGLayer", true, sp.getPosition(), 10, true);
	}
}
