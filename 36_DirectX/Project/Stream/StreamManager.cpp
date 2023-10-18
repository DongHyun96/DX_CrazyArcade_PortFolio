#include "Framework.h"
#include "StreamManager.h"


StreamManager::StreamManager()
{
	streamBlockManager = new StreamBlockManager;

	for (UINT i = 0; i < POOL_CNT; i++)
		streams.push_back(new Stream(streamBlockManager));

}

StreamManager::~StreamManager()
{
	for (Stream* stream : streams)
		delete stream;

	delete streamBlockManager;
}

void StreamManager::Update()
{
	for (Stream* stream : streams)
	{
		if (!stream->IsActive())
			continue;

		stream->Update();
	}
	
	streamBlockManager->Update();
}

void StreamManager::Render()
{
	streamBlockManager->Render();
}

void StreamManager::SpawnStream(const Util::Coord& spawnCoord, const UINT& streamLv)
{
	for (Stream* stream : streams)
	{
		if (stream->IsActive())
			continue;

		stream->Spawn(spawnCoord, streamLv);
		return;
	}
}

void StreamManager::Init()
{
	for (Stream* stream : streams)
		stream->Init();

	streamBlockManager->Init();
}
