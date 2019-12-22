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
}


AudioManager::~AudioManager()
{
	CkShutdown();
}

void AudioManager::update()
{
	CkUpdate();
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
	//	ckbファイルの指定
	CkBank* bank = CkBank::newBank(pass.c_str());
	//	再生したい音の名前を指定
	CkSound* sound = CkSound::newBankSound(bank, soundName.c_str());
	sound->play();
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
	_music->setLoopCount(-1);
	_music->play();
}
