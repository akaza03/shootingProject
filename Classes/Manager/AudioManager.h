#pragma once
#include <memory>
#include <cocos2d.h>

class CkSound;

#define lpAudioManager AudioManager::GetInstance()

enum SoundType
{
	S_BGM,
	S_SE,
	S_MAX
};

using AudioList = std::map < std::string, CkSound* >;

class AudioManager
{
public:
	static AudioManager& GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new AudioManager();
		}
		return *s_Instance;
	}
	~AudioManager();

	void update();

	//	���̍Đ�(�X�g���[�~���O�̏ꍇ�̓t�@�C�����A�I���������̏ꍇ�̓T�E���h��)
	void SetSound(const std::string name);

	//	����S��~(Scene�؂�ւ����ȂǂɌĂ�)
	void ResetAudio();

	//	�w�肵�������~������
	void StopSound(const std::string name);

	//	�o�b�N�O���E���h���Ȃ�BGM���ꎞ��~������
	void PauseAudio();

	//	BGM���ĊJ������
	void ReStartAudio();

private:
	AudioManager();
	static AudioManager* s_Instance;

	void AudioListInit();																	//	�t�@�C���̏���ꊇ�ǂݍ���
	void SetBank(const std::string &name, const std::string &soundName, SoundType type);	//	�I���������Đ�
	void SetStream(const std::string &name, SoundType type);								//	�X�g���[�~���O�Đ�

	AudioList audioList;
};

