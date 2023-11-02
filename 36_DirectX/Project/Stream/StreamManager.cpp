#include "Framework.h"
#include "StreamManager.h"

StreamBlockManager* StreamManager::streamBlockManager{};

StreamManager::StreamManager()
{
	static bool stb_mgr_inited = false;

	if (!stb_mgr_inited)
	{
		streamBlockManager = new StreamBlockManager;
		stb_mgr_inited = true;
	}

	for (UINT i = 0; i < POOL_CNT; i++)
		streams.push_back(new Stream);
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
