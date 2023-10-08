#include "Framework.h"
#include "StreamManager.h"


StreamManager::StreamManager()
{
	for (UINT i = 0; i < POOL_CNT; i++)
		streams.push_back(new Stream);
}

StreamManager::~StreamManager()
{
	for (Stream* stream : streams)
		delete stream;
}

void StreamManager::Update()
{
	for (Stream* stream : streams)
	{
		if (!stream->IsActive())
			continue;

		stream->Update();
	}
}

void StreamManager::Render()
{
	for (Stream* stream : streams)
	{
		if (!stream->IsActive())
			continue;

		stream->Render();
	}
}

void StreamManager::Spawn(const Util::Coord& spawnCoord, const UINT& streamLv) // Call once
{
	for (Stream* stream : streams)
	{
		if (stream->IsActive())
			continue;

		stream->Spawn(spawnCoord, streamLv);
		return;
	}
}
