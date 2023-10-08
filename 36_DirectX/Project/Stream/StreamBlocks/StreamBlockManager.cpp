#include "Framework.h"
#include "StreamBlockManager.h"


StreamBlockManager::StreamBlockManager()
{

	for (UINT i = 0; i < CENTER_POOL_CNT; i++)
		centerBlocks.push_back(new StreamBlock_Center);

	for (UINT i = 0; i < DIR_POOL_CNT; i++)
	{
		dirStreamMap[DIR_LEFT].push_back(new StreamBlock_Left);
		dirStreamMap[DIR_RIGHT].push_back(new StreamBlock_Right);
		dirStreamMap[DIR_UP].push_back(new StreamBlock_Up);
		dirStreamMap[DIR_DOWN].push_back(new StreamBlock_Down);
	}
}

StreamBlockManager::~StreamBlockManager()
{
	for (StreamBlock* block : centerBlocks)
		delete block;

	centerBlocks.clear();

	for (auto& p : dirStreamMap)
	{
		for (StreamBlock* block : p.second)
			delete block;
	}

	dirStreamMap.clear();
}

void StreamBlockManager::Update()
{
	for (StreamBlock* block : centerBlocks)
	{
		if (!block->IsActive())
			continue;

		block->Update();
	}

	for (auto& p : dirStreamMap)
	{
		for (StreamBlock* block : p.second)
		{
			if (!block->IsActive())
				continue;

			block->Update();
		}
	}


}

void StreamBlockManager::Render()
{
	for (StreamBlock* block : centerBlocks)
	{
		if (!block->IsActive())
			continue;

		block->Render();
	}

	for (auto& p : dirStreamMap)
	{
		for (StreamBlock* block : p.second)
		{
			if (!block->IsActive())
				continue;

			block->Render();
		}
	}
}

StreamBlock* StreamBlockManager::GetAvailableBlock(const Direction& dir)
{
	if (dir == DIR_NONE)
	{
		for (StreamBlock* block : centerBlocks)
		{
			if (block->IsActive()) continue;

			return block;
		}
		return nullptr;
	}

	for (StreamBlock* block : dirStreamMap[dir])
	{
		if (block->IsActive()) continue;

		return block;
	}
	return nullptr;
}

StreamBlock* StreamBlockManager::Spawn(const Direction& dir, const Util::Coord& spawnCoord, const bool& isEnd)
{
	if (dir == DIR_NONE)
	{
		for (StreamBlock* block : centerBlocks)
		{
			if (block->IsActive())
				continue;

			return block->Spawn(spawnCoord);
		}
		return nullptr;
	}

	for (StreamBlock* block : dirStreamMap[dir])
	{
		if (block->IsActive())
			continue;

		return block->Spawn(spawnCoord, isEnd);
	}
	return nullptr;

}



