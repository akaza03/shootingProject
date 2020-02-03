#pragma once
//#ifndef __HELLOWORLD_SCENE_H__
//#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include "Input/OprtKey.h"
#include "Input/UseKey.h"

//	�V�X�e���p�L�[(now,old)
using systemKey = std::map <UseKey, std::pair<bool, bool>>;

class TitleScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

private:
	void update(float d);
	void SetCredit();
	void SetCrText(std::string str, int size, int &cor);

	void SetUI();

	OprtState *_oprtState;					//	�V�X�e���p�̑��쐧��

	systemKey key;

	cocos2d::Layer * creditLayer;

	bool gameButtonFlag = true;				//	true�Ȃ�Q�[���X�^�[�g�Afalse�Ȃ�N���W�b�g
	bool creditFlag = false;				//	�N���W�b�g�\�L���Ȃ�true

	CREATE_FUNC(TitleScene);
};

