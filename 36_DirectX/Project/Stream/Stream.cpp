#include "Framework.h"
#include "Stream.h"



Stream::Stream(StreamBlockManager* streamBlockManager)
	:streamBlockManager(streamBlockManager)
{
}

Stream::~Stream()
{
	activatedBlocks.clear();
}

void Stream::Update()
{
	if (!isActive)
		return;

	HandleSpawning();
	HandleSelfActive();
}

void Stream::Spawn(const Util::Coord& spawnCoord, const UINT& streamLv)
{
	InitReachedMap(spawnCoord, streamLv);

	isActive = true;

	blockSpawnTime = 0.f;
	stopSpawning = false;
	activatedBlocks.clear();

	// Center���� ���⼭ ó��
	StreamBlock* block = streamBlockManager->Spawn(DIR_NONE, spawnCoord);
	activatedBlocks.push_back(block);
}

void Stream::InitReachedMap(const Util::Coord& spawnCoord, const UINT& streamLv)
{
	reachedCoordMap.clear();

	pair<int, int> curCoord{ spawnCoord.x, spawnCoord.y }; // 6, 7

	// Left
	for (UINT i = 1; i <= streamLv; i++)
	{
		curCoord.first--;

		if (curCoord.first < 0) // ���� ����
			break;

		reachedCoordMap[DIR_LEFT].push_back(Util::Coord(curCoord.first, curCoord.second));

		Block* targetBlock = GM->GetBlockManager()->GetCoordBlock(Util::Coord(curCoord.first, curCoord.second));

		if (!targetBlock) continue;
		
		if (!targetBlock->IsActive() || targetBlock->IsHidable()) continue;

		break;
	}

	// Right
	curCoord = { spawnCoord.x, spawnCoord.y };

	for (UINT i = 1; i <= streamLv; i++)
	{
		curCoord.first++;

		if (curCoord.first >= MAP_COL) // ���� ����
			break;

		reachedCoordMap[DIR_RIGHT].push_back(Util::Coord(curCoord.first, curCoord.second));

		Block* targetBlock = GM->GetBlockManager()->GetCoordBlock(Util::Coord(curCoord.first, curCoord.second));

		if (!targetBlock) continue;
		if (!targetBlock->IsActive() || targetBlock->IsHidable()) continue;
		break;
	}

	// Up
	curCoord = { spawnCoord.x, spawnCoord.y };

	for (UINT i = 1; i <= streamLv; i++)
	{
		curCoord.second++;

		if (curCoord.second >= MAP_ROW) // ���� ����
			break;

		reachedCoordMap[DIR_UP].push_back(Util::Coord(curCoord.first, curCoord.second));

		Block* targetBlock = GM->GetBlockManager()->GetCoordBlock(Util::Coord(curCoord.first, curCoord.second));

		if (!targetBlock) continue;
		if (!targetBlock->IsActive() || targetBlock->IsHidable()) continue;
		break;
	}

	// Down
	curCoord = { spawnCoord.x, spawnCoord.y };

	for (UINT i = 1; i <= streamLv; i++)
	{
		curCoord.second--;

		if (curCoord.second < 0) // ���� ����
			break;

		reachedCoordMap[DIR_DOWN].push_back(Util::Coord(curCoord.first, curCoord.second));

		Block* targetBlock = GM->GetBlockManager()->GetCoordBlock(Util::Coord(curCoord.first, curCoord.second));

		if (!targetBlock) continue;
		if (!targetBlock->IsActive() || targetBlock->IsHidable()) continue;
		break;
	}
}

void Stream::HandleSpawning()
{
	if (stopSpawning) return;

	blockSpawnTime += Time::Delta();

	if (blockSpawnTime < BLOCK_SPAWN_DELTA) return;
	
	blockSpawnTime -= BLOCK_SPAWN_DELTA;

	UINT dequeEmptyCnt{};

	for (UINT i = 0; i < 4; i++) 
	{
		Direction dir = (Direction)i;

		// ������ - �ƿ� ���� ���� �ֱ� ������ continue �ɾ� ��
		if (reachedCoordMap[dir].empty())
		{
			dequeEmptyCnt++;
			continue; 
		}

		Util::Coord spawnCoord = reachedCoordMap[dir].front();

		reachedCoordMap[dir].pop_front();

		bool isEnd = reachedCoordMap[dir].empty();

		StreamBlock* spawnedBlock = streamBlockManager->Spawn(dir, spawnCoord, isEnd);
		activatedBlocks.push_back(spawnedBlock);
	}

	if (dequeEmptyCnt >= 4) // �� �̻� spawn��ų streamBlock�� ����
	{
		stopSpawning = true;
		return;
	}
}

void Stream::HandleSelfActive()
{
	

	for (StreamBlock* block : activatedBlocks)
	{
		if (block->IsActive()) return;
	}

	// isActive�� ��� ���� ����

	isActive = false;
}
