#include "Character.h"
#include "Shot.h"

Shot::Shot()
{
}

Shot::~Shot()
{
}

void Shot::SetInit(std::string ImagePass, cocos2d::Sprite & sp, ActData &chara, float sPower, float sSpeed)
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
	distance += speed;

	auto winSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	TypeUpdate();

	if (hitObj || hitChara || distance >= winSize.width)
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

CharaType Shot::GetType()
{
	return type;
}

float Shot::GetPower()
{
	return power;
}

bool Shot::GetAtkFlag()
{
	return atkFlag;
}

void Shot::SetHitChara(bool flag)
{
	hitChara = flag;
}

void Shot::TypeInit(ActData & chara)
{
	//	�v���C���[3(�ǂɓ�����܂Ŕ��肪�������Ȃ�)
	if (type == CharaType::PLAYER && charaID == 2)
	{
		this->getChildByName("shot")->setOpacity(100);
		atkFlag = false;
	}
}

void Shot::TypeUpdate()
{
	//	�v���C���[3
	if (type == CharaType::PLAYER && charaID == 2)
	{
		if (hitObj && !atkFlag)
		{
			atkFlag = true;
			this->getChildByName("shot")->setOpacity(255);
		}
		hitObj = false;
	}
}

void Shot::HitCheck()
{
	////	�L�����N�^�[�Ƃ̔���
	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
	auto layer = nowScene->getChildByName("EMLayer");
	if (type == CharaType::ENEMY)
	{
		layer = nowScene->getChildByName("PLLayer");
	}

	for (auto obj : layer->getChildren())
	{
		//	����pBOX
		auto objBox = obj->boundingBox();
		auto charaBox = this->boundingBox();

		if (charaBox.intersectsRect(objBox))
		{
			//	���������ꍇ�̓_���[�W�d��
			hitChara = true;
		}
		else
		{
			hitChara = false;
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

