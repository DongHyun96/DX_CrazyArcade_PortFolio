#include "Framework.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
	System_Create(&system);

	system->init(MAX_CHANNEL, FMOD_INIT_NORMAL, nullptr);

	AddSound("GameStart", "_Sound/GameStart.mp3");

	AddSound("BalloonDeploy", "_Sound/BalloonDeploy.wav");
	AddSound("BalloonExplode", "_Sound/bombExplode.wav");
	AddSound("ItemSpawned", "_Sound/ItemGen.mp3");
	AddSound("ItemEarned", "_Sound/SetItem.wav");
	AddSound("VillageBGM", "_Sound/Boomhill.mp3", true);

	AddSound("Captured", "_Sound/inBalloon.mp3");
	AddSound("Saved", "_Sound/Saved.wav");
	AddSound("Die", "_Sound/Die.wav");

	AddSound("Lose", "_Sound/defeat.mp3");
	AddSound("Win", "_Sound/win.wav");
	AddSound("Draw", "_Sound/draw.mp3");

}

SoundManager::~SoundManager()
{
	for (pair<string, SoundInfo*> pair : sounds)
		delete pair.second;

	sounds.clear();

	system->release();
}

void SoundManager::Update()
{
	system->update();
}

void SoundManager::AddSound(string key, string path, bool stream)
{
	SoundInfo* info = new SoundInfo();

	if (stream)
	{
		system->createStream(path.c_str(), FMOD_LOOP_NORMAL, nullptr, &info->sound);
	}
	else
	{
		system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &info->sound);
	}

	sounds.emplace(key, info);
}

void SoundManager::Play(string key, float volume)
{
	if (sounds.count(key) == 0)
		return;

	system->playSound(sounds[key]->sound, nullptr, false, &sounds[key]->channel);

	sounds[key]->channel->setVolume(volume);
}

void SoundManager::Stop(string key)
{
	if (sounds.count(key) == 0)
		return;

	sounds[key]->channel->stop();
}

void SoundManager::Pause(string key)
{
	if (sounds.count(key) == 0)
		return;

	sounds[key]->channel->setPaused(true);
}

void SoundManager::Resume(string key)
{
	if (sounds.count(key) == 0)
		return;

	sounds[key]->channel->setPaused(false);
}

