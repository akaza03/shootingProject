/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <memory>
#include <Effekseer/Effekseer.h>
#include "Input/OprtKey.h"
#include "Input/UseKey.h"
#include "ck/sound.h"

enum LayerNumber
{
	BG,						//	�o�b�N�O���E���h�p���C���[
	PL,						//	�v���C���[&�U���p���C���[
	EM,						//	�G�l�~�[&�U���p���C���[
	UI,						//	UI�p���C���[
	BW,						//	��ʂ��Â����郌�C���[(�|�[�Y��ʂȂ�)
	FG,						//	�t�����g�O���E���h�p���C���[
	DB,						//	�f�o�b�O�p���C���[
	LAYER_MAX
};

//	�V�X�e���p�L�[(now,old)
using systemKey = std::map <UseKey, std::pair<bool,bool>>;


class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

private:
	cocos2d::Layer * BGLayer;				//	�o�b�N�O���E���h�p���C���[
	cocos2d::Layer * PLLayer;				//	�v���C���[&�U���p���C���[
	cocos2d::Layer * EMLayer;				//	�G�l�~�[&�U���p���C���[
	cocos2d::Layer * UILayer;				//	UI�p���C���[
	cocos2d::Layer * BWLayer;				//	��ʂ��Â����郌�C���[(�|�[�Y��ʂȂ�)
	cocos2d::Layer * FGLayer;				//	�t�����g�O���E���h�p���C���[
	cocos2d::Layer * DBLayer;				//	�f�o�b�O�p���C���[

	OprtState *_oprtState;					//	�V�X�e���p�̑��쐧��

	systemKey key;

	void update(float d);

	void keyUpdate();

	void pause(cocos2d::Layer *layer);				//	�|�[�Y���ȂǗp�̒�~����

	bool pauseFlag;									//	��ʒ�~�p�t���O

	bool gameEndFlag;								//	�Q�[���I�[�o�[or�Q�[���N���A�t���O

	int enemyCnt;									//	�G�̐�

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
