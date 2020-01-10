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

	OprtState *_oprtState;					//	�V�X�e���p�̑��쐧��

	systemKey key;
	CREATE_FUNC(TitleScene);
};

