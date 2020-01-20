#include "Unit/Character.h"
#include "Unit/Shot.h"
#include "DamageCheck.h"

bool DamageCheck::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();

	auto layer = nowScene->getChildByName("ATKLayer");

	//	攻撃レイヤーとの判定
	if (act.damageCnt <= 0 && act.invTime <= 0)
	{
		for (auto obj : layer->getChildren())
		{
			//	判定用BOX
			auto objBox = obj->boundingBox();
			auto charaBox = sp.boundingBox();

			Shot* shot = (Shot*)obj;
			if ((shot->GetType() == CharaType::PLAYER && act.cType == CharaType::ENEMY)
				|| (shot->GetType() == CharaType::ENEMY && act.cType == CharaType::PLAYER))
			{
				if (charaBox.intersectsRect(objBox) && shot->GetAtkFlag())
				{
					//	当たった場合はダメージ硬直
					act.damageCnt = 20;
					shot->SetHitChara(true);

					//	ダメージ
					act.HP -= shot->GetPower();
				}
			}
		}
	}

	if (act.anim == AnimState::DAMAGE)
	{
		act.damageCnt--;
		//	ダメージ硬直が終わった瞬間に無敵を付与する
		if (act.damageCnt == 0)
		{
			if (act.cType == CharaType::PLAYER)
			{
				act.invTime = 30;
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
