#include "Unit/Character.h"
#include "DamageCheck.h"

bool DamageCheck::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();

	auto layer = nowScene->getChildByName("PLLayer");
	if (act.cType == CharaType::PLAYER)
	{
		layer = nowScene->getChildByName("EMLayer");
	}

	//	攻撃レイヤーとの判定
	if (act.damageCnt <= 0 && act.invTime <= 0)
	{
		for (auto obj : layer->getChildren())
		{
			//	判定用BOX
			auto objBox = obj->boundingBox();
			auto charaBox = sp.boundingBox();

			if (charaBox.intersectsRect(objBox))
			{
				//	当たった場合はダメージ硬直
				act.damageCnt = 20;

				//	ダメージ
				act.HP -= 5;
			}
		}
	}

	if (act.anim == AnimState::DAMAGE)
	{
		act.damageCnt--;
		//	ダメージ硬直が終わった瞬間に無敵を付与する
		if (act.damageCnt == 0)
		{
			act.invTime = 10;
			//auto blink = cocos2d::Blink::create(1, 20);
			//sp.runAction(blink);
		}
	}

	if (act.invTime > 0)
	{
		act.invTime--;
	}

	return false;
}
