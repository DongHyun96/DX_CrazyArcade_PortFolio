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

	// Center 먼저 스폰 시킴
	StreamBlock* block = streamBlockManager->Spawn(DIR_NONE, spawnCoord);

	activatedBlocks.push_back(block);

	HandleChainExplosion();
}

void Stream::InitReachedMap(const Util::Coord& spawnCoord, const UINT& streamLv)
{
	reachedCoordMap.clear();

	vector<int> dx = {0, 0, -1, 1}; // U, D, L, R
	vector<int> dy = { 1, -1, 0, 0};

	for (UINT i = 0; i < 4; i++)
	{
		Direction dir = (Direction)i;
		pair<int, int> curCoord{ spawnCoord.x, spawnCoord.y };
		

		for (UINT j = 1; j <= streamLv; j++)
		{
			curCoord.first += dx[i];
			curCoord.second += dy[i];
			
			// 범위 판정
			if ( curCoord.first < 0 || curCoord.first >= MAP_COL ||
				curCoord.second < 0 || curCoord.second >= MAP_ROW )
				break;

			reachedCoordMap[dir].push_back(Util::Coord(curCoord.first, curCoord.second));

			Block* targetBlock = GM->GetBlockManager()->GetCoordBlock(Util::Coord(curCoord.first, curCoord.second));

			if (!targetBlock) continue;
			if (!targetBlock->IsActive() || targetBlock->IsHidable()) continue;
			break;
		}
	}
}

void Stream::HandleChainExplosion()
{
	for (Balloon* balloon : GM->GetBalloonManager()->GetNormalBalloons())
	{
		if (!balloon->Active())
			continue;

		for (auto& p : reachedCoordMap)
		{
			for (auto& coord : p.second)
			{
				if (balloon->GetSpawnCoord() == coord)
					balloon->Explode();
			}
		}
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

		// 문제점 - 아예 없을 수도 있기 때문에 continue 걸어 둠
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

	if (dequeEmptyCnt >= 4) // 더 이상 spawn시킬 streamBlock이 없음
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
	
	activatedBlocks.clear();
	isActive = false;
}
