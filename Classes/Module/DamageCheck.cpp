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

	//	�U�����C���[�Ƃ̔���
	if (act.damageCnt <= 0 && act.invTime <= 0)
	{
		for (auto obj : layer->getChildren())
		{
			//	����pBOX
			auto objBox = obj->boundingBox();
			auto charaBox = sp.boundingBox();

			if (charaBox.intersectsRect(objBox))
			{
				//	���������ꍇ�̓_���[�W�d��
				act.damageCnt = 20;

				//	�_���[�W
				act.HP -= 5;
			}
		}
	}

	if (act.anim == AnimState::DAMAGE)
	{
		act.damageCnt--;
		//	�_���[�W�d�����I������u�Ԃɖ��G��t�^����
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
