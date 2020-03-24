#include "Character.h"
#include "Shot.h"

Shot::Shot()
{
}

Shot::~Shot()
{
}

void Shot::SetInit(std::string ImagePass, cocos2d::Sprite & sp, ActData &chara, float sPower, float sSpeed, float stun)
{
	hitChara = false;
	hitObj = false;
	auto charaPos = sp.getPosition();

	setPosition(charaPos);
	//	�����ɂ���č��W������������̕ύX
	if (chara.dir == DIR::LEFT)
	{
		setPosition(cocos2d::Vec2(charaPos.x - sp.getContentSize().width / 2, charaPos.y));
		speed = -sSpeed;
	}
	else if (chara.dir == DIR::RIGHT)
	{
		setPosition(cocos2d::Vec2(charaPos.x + sp.getContentSize().width / 2, charaPos.y));
		speed = sSpeed;
	}

	power = sPower;
	stunTime = stun;

	//	Shot�ɉ摜�̒ǉ�
	this->addChild(Sprite::create(ImagePass),0,"shot");

	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();

	auto layer = nowScene->getChildByName("ATKLayer");

	type = chara.cType;
	charaID = chara.charaID;
	atkFlag = true;

	TypeInit(chara);

	this->setCameraMask(static_cast<int>(cocos2d::CameraFlag::USER1), true);
	
	layer->addChild(this,0);

	this->scheduleUpdate();
}

void Shot::update(float d)
{
	this->setPosition(getPosition().x + speed, getPosition().y);
	distance += abs(speed);

	auto winSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	TypeUpdate();

	if (hitObj || hitChara || distance >= winSize.width / 2)
	{
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		auto layer = nowScene->getChildByName("ATKLayer");
		layer->removeChild(this);
	}
	else
	{
		HitCheck();
	}
}

void Shot::TypeInit(ActData & chara)
{
	throwFlag = false;
	//	�v���C���[3(�ǂɓ�����܂Ŕ��肪�������Ȃ�)
	if (type == CharaType::PLAYER && charaID == 2)
	{
		this->getChildByName("shot")->setOpacity(100);
		atkFlag = false;
	}

	//	�G�l�~�[3(�����Z)
	if (type == CharaType::ENEMY && charaID == 3)
	{
		this->getChildByName("shot")->setOpacity(0);
		distance = cocos2d::Director::getInstance()->getOpenGLView()->
					getDesignResolutionSize().width / 2 - abs(speed) * 2;
		throwFlag = true;
	}
}

void Shot::TypeUpdate()
{
	//	�v���C���[2(�ђʒe)
	if (type == CharaType::PLAYER && charaID == 1)
	{
		hitChara = false;
	}
	//	�v���C���[3
	if (type == CharaType::PLAYER && charaID == 2)
	{
		if (hitObj)
		{
			distance += 10;
			if (!atkFlag)
			{
				atkFlag = true;
				this->getChildByName("shot")->setOpacity(255);
			}
		}
		hitObj = false;
	}
}

void Shot::HitCheck()
{
	//	�G�̒e�Ƃ̔���
	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
	auto layer = nowScene->getChildByName("ATKLayer");

	auto charaBox = cocos2d::Rect(this->getPosition(), this->getChildByName("shot")->getContentSize()/2);

	hitChara = false;

	for (auto obj : layer->getChildren())
	{
		auto objBox = obj->boundingBox();

		Shot* shot = (Shot*)obj;
		if ((shot->GetType() == CharaType::PLAYER && type == CharaType::ENEMY)
			|| (shot->GetType() == CharaType::ENEMY && type == CharaType::PLAYER))
		{
			if (charaBox.intersectsRect(objBox) && shot->GetAtkFlag() && atkFlag)
			{
				if (!(type == CharaType::PLAYER && charaID == 1))
				{
   					shot->SetHitChara(true);
				}
				if (!(shot->GetType() == CharaType::PLAYER && shot->GetID() == 1))
				{
					hitChara = true;
				}
			}
		}
	}

	//	��Q���Ƃ̔���

	//	�Փ˗p�̃��C���[�̎擾
	auto director = cocos2d::Director::getInstance();
	auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BGLayer")->getChildByName("stageMap");
	auto layerMap = map->getLayer("collision");

	//	�e�̍��W
	auto pos = cocos2d::Vec2(getPosition().x, layerMap->getLayerSize().height * layerMap->getMapTileSize().height - getPosition().y);
	//	�w�肳�ꂽ�ꏊ�̃^�C��ID
	int tile = 0;

	//	�}�b�v�Ƃ̓����蔻��
	auto colPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width, (pos.y + getContentSize().height / 2) / layerMap->getMapTileSize().height);

	if (colPos.x > 0 && colPos.x < layerMap->getLayerSize().width
		&&	colPos.y > 0 && colPos.y < layerMap->getLayerSize().height)
	{
		//	�^�C���̎擾
		tile = layerMap->getTileGIDAt(colPos);
	}

	if (tile != 0)
	{
		hitObj =  true;
	}
	else
	{
		hitObj = false;
	}
}

CharaType Shot::GetType()
{
	return type;
}

int Shot::GetID()
{
	return charaID;
}

float Shot::GetPower()
{
	return power;
}

float Shot::GetSpeed()
{
	return speed;
}

float Shot::GetStunTime()
{
	return stunTime;
}

bool Shot::GetAtkFlag()
{
	return atkFlag;
}

bool Shot::GetThrow()
{
	return throwFlag;
}

void Shot::SetHitChara(bool flag)
{
	hitChara = flag;
}