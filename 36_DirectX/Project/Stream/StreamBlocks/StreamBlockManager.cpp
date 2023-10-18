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

void StreamBlockManager::Init()
{
	for (StreamBlock* block : centerBlocks)
		block->Init();

	for (auto& p : dirStreamMap)
		for (StreamBlock* block : p.second) block->Init();
			
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

	HandleCollision();

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

void StreamBlockManager::HandleCollision()
{

	for (StreamBlock* streamBlock : centerBlocks)
	{
		if (!streamBlock->IsActive()) continue;

		HandleBlockCollision(streamBlock);
		HandleItemCollision(streamBlock);

		if (!streamBlock->IsActive()) continue;

		for (Character* player : PM->GetWholePlayers())
			streamBlock->GetBody()->AABBCollision(player->GetBody()->GlobalPosition(), player);

	}

	for (auto& p : dirStreamMap)
	{
		for (StreamBlock* streamBlock : p.second)
		{
			if (!streamBlock->IsActive()) continue;

			HandleBlockCollision(streamBlock);
			HandleItemCollision(streamBlock);

			if (!streamBlock->IsActive()) continue;

			for (Character* player : PM->GetWholePlayers())
				streamBlock->GetBody()->AABBCollision(player->GetBody()->GlobalPosition(), player);

		}
	}
}


void StreamBlockManager::HandleBlockCollision(StreamBlock* streamBlock)
{
	Block* block = GM->GetBlockManager()->GetCoordBlock(streamBlock->GetSpawnCoord());

	if (!block) return;
	if (!block->IsActive()) return;

	streamBlock->GetBody()->AABBCollision(block->GetBody(), block);
}

void StreamBlockManager::HandleItemCollision(StreamBlock* streamBlock)
{
	if (!streamBlock->IsActive()) return;

	for (Item* item : ItemManager::GetItems())
	{
		if (!item->GetIsActive()) continue;

		streamBlock->GetBody()->AABBCollision(item->GetBody()->GlobalPosition(), item);
	}

}


