#include "Unit/Character.h"
#include "Unit/Shot.h"
#include "DamageCheck.h"

bool DamageCheck::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();

	auto layer = nowScene->getChildByName("ATKLayer");

	//	�U�����C���[�Ƃ̔���
	if (act.damageCnt <= 0 && act.invTime <= 0)
	{
		for (auto obj : layer->getChildren())
		{
			//	����pBOX
			auto objBox = obj->boundingBox();
			auto charaBox = sp.boundingBox();

			Shot* shot = (Shot*)obj;
			if ((shot->GetType() == CharaType::PLAYER && act.cType == CharaType::ENEMY)
				|| (shot->GetType() == CharaType::ENEMY && act.cType == CharaType::PLAYER))
			{
				if (charaBox.intersectsRect(objBox) && shot->GetAtkFlag())
				{
					//	���������ꍇ�̓_���[�W�d��
					act.damageCnt = 20;
					shot->SetHitChara(true);

					//	�_���[�W
					act.HP -= shot->GetPower();
				}
			}
		}
	}

	if (act.anim == AnimState::DAMAGE)
	{
		act.damageCnt--;
		//	�_���[�W�d�����I������u�Ԃɖ��G��t�^����
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
		//	���G���̓_�ŗp
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

	//	�X�e�[�W�O�ɏo���玀�S
	if (sp.getPosition().y < -sp.getContentSize().height)
	{
		act.HP = 0;
	}

	//	HP������𒴂��Ȃ��悤��
	if (act.HP > act.MaxHP)
	{
		act.HP = act.MaxHP;
	}

	return false;
}
