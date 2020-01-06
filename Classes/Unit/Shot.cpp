#include "Character.h"
#include "Shot.h"

Shot::Shot()
{
}

Shot::~Shot()
{
}

void Shot::SetInit(std::string ImagePass, cocos2d::Sprite & sp, ActData &chara, float sSpeed)
{
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

	//	Shot�ɉ摜�̒ǉ�
	this->addChild(Sprite::create(ImagePass));

	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();

	//	�������L�����̎�ނɂ���ă��C���[����
	auto layer = nowScene->getChildByName("PLLayer");
	if (chara.cType == CharaType::ENEMY)
	{
		layer = nowScene->getChildByName("EMLayer");
	}

	type = chara.cType;
	
	layer->addChild(this,0);

	this->scheduleUpdate();
}

void Shot::update(float d)
{
	this->setPosition(getPosition().x + speed, getPosition().y);
	distance += speed;
	if (hitCheck() || distance >= 500)
	{
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		auto layer = nowScene->getChildByName("PLLayer");
		if (type == CharaType::ENEMY)
		{
			layer = nowScene->getChildByName("EMLayer");
		}
		layer->removeChild(this);
	}
}

bool Shot::hitCheck()
{
	////	�L�����N�^�[�Ƃ̔���
	//auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
	//auto layer = nowScene->getChildByName("EMLayer");
	//if (type == CharaType::ENEMY)
	//{
	//	layer = nowScene->getChildByName("PLLayer");
	//}

	//for (auto obj : layer->getChildren())
	//{
	//	//	����pBOX
	//	auto objBox = obj->boundingBox();
	//	auto charaBox = this->boundingBox();

	//	if (charaBox.intersectsRect(objBox))
	//	{
	//		//	���������ꍇ�̓_���[�W�d��
	//		return true;
	//	}
	//}

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
		return true;
	}
	return false;
}

