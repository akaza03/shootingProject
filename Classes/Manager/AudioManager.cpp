#include "cricket/inc/ck/ck.h"
#include "cricket/inc/ck/config.h"
#include "cricket/inc/ck/bank.h"
#include "cricket/inc/ck/sound.h"
#include "AudioManager.h"

AudioManager* AudioManager::s_Instance = nullptr;

AudioManager::AudioManager()
{
#if CK_PLATFORM_ANDROID
	//CkConfig config(cocos2d::JniHelper::getEnv(), cocos2d::JniHelper::getActivity());
#else
	CkConfig config;
	CkInit(&config);
#endif

	AudioListInit();
}


AudioManager::~AudioManager()
{
	for (auto &itr : audioList)
	{
		itr.second->destroy();
	}
	audioList.erase(audioList.begin(), audioList.end());

	CkShutdown();
}

void AudioManager::AudioListInit()
{
	SetStream("titleBGM.cks", SoundType::S_BGM);
	SetStream("music.cks", SoundType::S_BGM);
	SetBank("Sound.ckb", "click", SoundType::S_SE);
	SetBank("Sound.ckb", "shot", SoundType::S_SE);
}

void AudioManager::update()
{
	CkUpdate();
}

void AudioManager::SetSound(const std::string name)
{
	auto sound = audioList[name];
	if (sound != nullptr)
	{
		sound->play();
	}
}

void AudioManager::ResetAudio()
{
	for (auto &itr : audioList)
	{
		itr.second->stop();
	}
	//audioList.erase(audioList.begin(), audioList.end());
}

void AudioManager::StopSound(const std::string name)
{
	auto sound = audioList[name];
	if (sound != nullptr)
	{
		sound->stop();
	}
}


void AudioManager::SetBank(const std::string &name, const std::string &soundName, SoundType type)
{
	std::string pass;
#if CK_PLATFORM_ANDROID
	if (type == SoundType::S_BGM)
	{
		pass = "Audio/BGM/" + name;
	}
	else if (type == SoundType::S_SE)
	{
		pass = "Audio/SE/" + name;
	}
#else
	if (type == SoundType::S_BGM)
	{
		pass = "Resources/Audio/BGM/" + name;
	}
	else if (type == SoundType::S_SE)
	{
		pass = "Resources/Audio/SE/" + name;
	}
#endif
	//	ckb�t�@�C���̎w��
	CkBank* bank = CkBank::newBank(pass.c_str());
	if (bank != nullptr)
	{
		//	�Đ����������̖��O���w��
		CkSound* sound = CkSound::newBankSound(bank, soundName.c_str());
		if (sound != nullptr)
		{
			//sound->play();
			audioList[soundName] = sound;
		}
	}
}

void AudioManager::SetStream(const std::string &name, SoundType type)
{
	std::string pass;
#if CK_PLATFORM_ANDROID
	if (type == SoundType::S_BGM)
	{
		pass = "Audio/BGM/" + name;
	}
	else if (type == SoundType::S_SE)
	{
		pass = "Audio/SE/" + name;
	}
#else
	if (type == SoundType::S_BGM)
	{
		pass = "Resources/Audio/BGM/" + name;
	}
	else if (type == SoundType::S_SE)
	{
		pass = "Resources/Audio/SE/" + name;
	}
#endif

	CkSound* _music = CkSound::newStreamSound(pass.c_str());
	if (_music != nullptr)
	{
		_music->setLoopCount(-1);
		//_music->play();
		audioList[name] = _music;
	}
}
