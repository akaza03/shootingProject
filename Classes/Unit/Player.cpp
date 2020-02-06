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

			//	�L�[�̃`�F�b�N
			for (auto checkKey : _oprtState->GetKeyList())
			{
				//	���̃L�[���o�^����Ă���΃L�[���X�V����
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

			//	�^�b�`���W�̎擾
			if (_oprtState->GetTouchPoint() != oldTouchPos)
			{
				itr.second.touchPos = _oprtState->GetTouchPoint();
				oldTouchPos = itr.second.touchPos;
			}
			else
			{
				itr.second.touchPos = cocos2d::Vec2(-10, -10);
			}

			//	���݂�HP
			auto oldHp = itr.second.HP;
			//	���݂�charaID
			auto oldID = itr.second.charaID;

			//	���W���[�����g�p�����A�N�V��������
			ActModule()(*this, itr.second);

			//	�L�����N�^�[�̌��
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

			//	HP�o�[�̑���
			if (oldHp != itr.second.HP)
			{
				auto layer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("UILayer");
				cocos2d::Sprite* HPBar = (cocos2d::Sprite*) layer->getChildByName("hpBar");
				//	�ő�HP���猩�����݂�HP�̊���
				float HPPercent = (float)itr.second.HP / (float)itr.second.MaxHP;
				//	��U�߂�
				auto oldSize = HPBar->getScaleX();
				float ImageSizeX = HPBar->getContentSize().width * (1 - oldSize);
				HPBar->setPosition(HPBar->getPosition().x + ImageSizeX / 2, HPBar->getPosition().y);

				//	HP�o�[�̊g��k��(X���W�̂�)
				HPBar->setScale(HPPercent, 1);
				//	�����������̈ʒu�␳
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

			//	�O���̃`�F�b�N�p
			_actData.nowAnim = itr.second.nowAnim;
			_actData.damageCnt = itr.second.damageCnt;

			if (itr.second.nowAnim != itr.second.anim)
			{
				//	���̃A�j���[�V�����Ɍ��݂̃L�[����n������
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

				//	�L�[�̏�����
				for (auto itrKey : UseKey())
				{
					//	���̃A�j���[�V�����Ɍ��݂̃A�j���[�V�����̃L�[����n��
					std::get<0>(nextKey.key[itrKey]) = std::get<0>(itr.second.key[itrKey]);
					std::get<1>(nextKey.key[itrKey]) = std::get<1>(itr.second.key[itrKey]);
					//	���̃A�j���[�V�����̃L�[����������
					std::get<0>(itr.second.key[itrKey]) = false;
					std::get<1>(itr.second.key[itrKey]) = false;
				}
				//	�X�e�[�^�X��n��
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

