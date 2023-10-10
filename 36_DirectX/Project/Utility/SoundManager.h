#pragma once

#define MAX_CHANNEL 10 // 소리 채널 개수

struct SoundInfo
{
	~SoundInfo()
	{
		sound->release();
	}

	  Sound* sound;
	Channel* channel;
};

class SoundManager : public Singleton<SoundManager>
{
	friend class Singleton;
private:
	SoundManager();
	~SoundManager();

public:
	void Update();

	// stream - isLoop
	void AddSound(string key, string path, bool stream = false);

	void   Play(string key, float volume = 0.1f);
	void   Stop(string key);
	void  Pause(string key);
	void Resume(string key);

private:
	map<string, SoundInfo*> sounds;

	System* system;

	ChannelGroup* channelGroup;
};
