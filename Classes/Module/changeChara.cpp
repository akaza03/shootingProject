#include "Unit/Character.h"
#include "changeChara.h"


bool changeChara::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (act.cType == CharaType::PLAYER)
	{
		int number = act.charaID;
		int oldNumber = number;

		//	キャラクターのアイコン
		auto UI = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("UILayer");
		cocos2d::Sprite* p0 = (cocos2d::Sprite*)UI->getChildByName("p0Icon");
		cocos2d::Sprite* p1 = (cocos2d::Sprite*)UI->getChildByName("p1Icon");
		cocos2d::Sprite* p2 = (cocos2d::Sprite*)UI->getChildByName("p2Icon");

		cocos2d::Rect spriteRect = cocos2d::Rect(p1->getPosition().x - p1->getContentSize().width / 2,
			p1->getPosition().y - p1->getContentSize().width / 2,
			p1->getContentSize().width,
			p1->getContentSize().height);
		if (spriteRect.containsPoint(act.touchPos))
		{
			std::get<0>(act.key[UseKey::K_S]) = true;
		}

		spriteRect = cocos2d::Rect(p2->getPosition().x - p2->getContentSize().width / 2,
			p2->getPosition().y - p2->getContentSize().width / 2,
			p2->getContentSize().width,
			p2->getContentSize().height);
		if (spriteRect.containsPoint(act.touchPos))
		{
			std::get<0>(act.key[UseKey::K_A]) = true;
		}


		if ((std::get<0>(act.key[UseKey::K_A]) && !std::get<1>(act.key[UseKey::K_A])))
		{
			if (number <= 0)
			{
				number = 2;
			}
			else
			{
				number--;
			}
		}
		else if (std::get<0>(act.key[UseKey::K_S]) && !std::get<1>(act.key[UseKey::K_S]))
		{
			if (number >= 2)
			{
				number = 0;
			}
			else
			{
				number++;
			}
		}

		//	チェンジ時
		if (number != oldNumber)
		{
			if (act.changeCnt[number] == 0)
			{
				act.charaID = number;
				act.changeCnt[number] = 100;
				//	アイコンの切り替え
				switch (number)
				{
				case 0:
					p0->setSpriteFrame(cocos2d::Sprite::create(RES_ID("p0icon"))->getSpriteFrame());
					p1->setSpriteFrame(cocos2d::Sprite::create(RES_ID("p1icon"))->getSpriteFrame());
					p2->setSpriteFrame(cocos2d::Sprite::create(RES_ID("p2icon"))->getSpriteFrame());
					break;
				case 1:
					p0->setSpriteFrame(cocos2d::Sprite::create(RES_ID("p1icon"))->getSpriteFrame());
					p1->setSpriteFrame(cocos2d::Sprite::create(RES_ID("p2icon"))->getSpriteFrame());
					p2->setSpriteFrame(cocos2d::Sprite::create(RES_ID("p0icon"))->getSpriteFrame());
					break;
				case 2:
					p0->setSpriteFrame(cocos2d::Sprite::create(RES_ID("p2icon"))->getSpriteFrame());
					p1->setSpriteFrame(cocos2d::Sprite::create(RES_ID("p0icon"))->getSpriteFrame());
					p2->setSpriteFrame(cocos2d::Sprite::create(RES_ID("p1icon"))->getSpriteFrame());
					break;
				default:
					break;
				}

				lpEffectManager.SetEffect("effect/Laser01.efk", "FGLayer", sp.getPosition(), 20, true);
				lpAudioManager.SetBank("Sound.ckb", "shot", SoundType::S_SE);
			}
		}

		for (int i = 0; i < 3; i++)
		{
			if (act.changeCnt[i] > 0)
			{
				act.changeCnt[i]--;
			}
		}
	}
	return false;
}
