#include "Unit/Character.h"
#include "Unit/Shot.h"
#include "DamageCheck.h"

bool DamageCheck::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
	auto layer = nowScene->getChildByName("ATKLayer");

	auto charaBox = sp.boundingBox();
	//	�U�����C���[�Ƃ̔���
	for (auto obj : layer->getChildren())
	{
		//	����pBOX
		auto objBox = obj->boundingBox();

		Shot* shot = (Shot*)obj;
		if ((shot->GetType() == CharaType::PLAYER && act.cType == CharaType::ENEMY)
			|| (shot->GetType() == CharaType::ENEMY && act.cType == CharaType::PLAYER))
		{
			if (charaBox.intersectsRect(objBox) && shot->GetAtkFlag())
			{
				//	�e�ɏ��Ŕ���
				shot->SetHitChara(true);
				act.damageNumber = shot->GetPower();

				if (act.damageCnt <= 0 && act.invTime <= 0 && act.anim != AnimState::THROW && act.anim != AnimState::DAMAGE)
				{
					//	�U�����󂯂�����������
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

					//	���������ꍇ�̓_���[�W�d��
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
			//	�ǂɐڐG�����ꍇ�_���[�W�����Ɉڂ�
			if (act.checkPoint[DIR::LEFT] || act.checkPoint[DIR::RIGHT])
			{
				DoDamage(sp, act);
				act.damageCnt = 50;
				act.nowAnim = AnimState::DAMAGE;
			}
			else
			{
				//	�U�����󂯂������Ƌt�̕����ɐ������
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
		//	�_���[�W�d�����L�����N�^�[��h�炷
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
		//	�_���[�W�d�����I������u�Ԃɖ��G��t�^����
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

void DamageCheck::DoDamage(cocos2d::Sprite & sp, ActData & act)
{
	//	�_���[�W
	act.HP -= act.damageNumber;
	act.damageNumber = 0;
	if (act.HP > 0)
	{
		lpAudioManager.SetSound("damage");
		lpEffectManager.SetEffect((RES_ID("hitEff").c_str()), "FGLayer", true, sp.getPosition(), 10, true);
	}
}
