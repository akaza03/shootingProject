#pragma once
#include <memory>
#include <cocos2d.h>

#define lpAudioManager AudioManager::GetInstance()

enum SoundType
{
	S_BGM,
	S_SE,
	S_MAX
};

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

	void SetBank(const std::string &name, const std::string &soundName, SoundType type);		//	オンメモリ再生
	void SetStream(const std::string &name, SoundType type);									//	ストリーミング再生

private:
	AudioManager();
	static AudioManager* s_Instance;
};

