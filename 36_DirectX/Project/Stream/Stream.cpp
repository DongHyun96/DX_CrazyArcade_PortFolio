#include "Framework.h"
#include "Stream.h"


Stream::Stream()
{
	centerStream = new StreamBlock_Center;
	
	for (UINT i = 0; i < DIR_STREAM_CNT; i++)
	{
		dirStreamMap[DIR_LEFT].push_back(new StreamBlock_Left);
		dirStreamMap[DIR_RIGHT].push_back(new StreamBlock_Right);
		dirStreamMap[DIR_UP].push_back(new StreamBlock_Up);
		dirStreamMap[DIR_DOWN].push_back(new StreamBlock_Down);
	}
}

Stream::~Stream()
{
	delete centerStream;

	for (auto& p : dirStreamMap)
	{
		for (StreamBlock* sb : p.second)
			delete sb;
	}

	dirStreamMap.clear();
}

void Stream::Update()
{
	if (!isActive)
		return;

	centerStream->Update();

	for (auto& p : dirStreamMap)
	{
		for (StreamBlock* sb : p.second)
			sb->Update();
	}

	HandleSpawning();

	HandleActive();
}

void Stream::Render()
{
	if (!isActive)
		return;

	centerStream->Render();

	for (auto& p : dirStreamMap)
	{
		for (StreamBlock* sb : p.second)
			sb->Render();
	}
}

void Stream::Spawn(const Util::Coord& spawnCoord, const UINT& streamLv)
{
	InitReachedMap(spawnCoord, streamLv);

	isActive = true;

	blockSpawnTime = 0.f;
	curSpawnIdx = 0;
	stopSpawning = false;

	// Center먼저 여기서 처리
	centerStream->Spawn(spawnCoord);
}

void Stream::InitReachedMap(const Util::Coord& spawnCoord, const UINT& streamLv)
{
	reachedCoordMap.clear();

	pair<int, int> curCoord{ spawnCoord.x, spawnCoord.y };

	// Left
	for (UINT i = 1; i <= streamLv; i++)
	{
		curCoord.first -= i;

		if (curCoord.first < 0) // 범위 판정
			break;

		reachedCoordMap[DIR_LEFT].push_back(Util::Coord(curCoord.first, curCoord.second));

		Block* targetBlock = GM->GetBlockManager()->GetCoordBlock(Util::Coord(curCoord.first, curCoord.second));

		if (!targetBlock) continue;

		// 블록이 Hidable만 아니면 됨
		if (!targetBlock->IsActive() || !targetBlock->IsHidable()) continue;

		// 장애물에 stream이 걸림 (마지막 stream이 될 것임)
		break;
	}

	// Right
	curCoord = { spawnCoord.x, spawnCoord.y };

	for (UINT i = 1; i <= streamLv; i++)
	{
		curCoord.first += i;

		if (curCoord.first >= MAP_COL) // 범위 판정
			break;

		reachedCoordMap[DIR_RIGHT].push_back(Util::Coord(curCoord.first, curCoord.second));

		Block* targetBlock = GM->GetBlockManager()->GetCoordBlock(Util::Coord(curCoord.first, curCoord.second));

		if (!targetBlock) continue;
		if (!targetBlock->IsActive() || !targetBlock->IsHidable()) continue;
		break;
	}

	// Up
	curCoord = { spawnCoord.x, spawnCoord.y };

	for (UINT i = 1; i <= streamLv; i++)
	{
		curCoord.second += i;

		if (curCoord.second >= MAP_ROW) // 범위 판정
			break;

		reachedCoordMap[DIR_UP].push_back(Util::Coord(curCoord.first, curCoord.second));

		Block* targetBlock = GM->GetBlockManager()->GetCoordBlock(Util::Coord(curCoord.first, curCoord.second));

		if (!targetBlock) continue;
		if (!targetBlock->IsActive() || !targetBlock->IsHidable()) continue;
		break;
	}

	// Down
	curCoord = { spawnCoord.x, spawnCoord.y };

	for (UINT i = 1; i <= streamLv; i++)
	{
		curCoord.second -= i;

		if (curCoord.second < 0) // 범위 판정
			break;

		reachedCoordMap[DIR_DOWN].push_back(Util::Coord(curCoord.first, curCoord.second));

		Block* targetBlock = GM->GetBlockManager()->GetCoordBlock(Util::Coord(curCoord.first, curCoord.second));

		if (!targetBlock) continue;
		if (!targetBlock->IsActive() || !targetBlock->IsHidable()) continue;
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

		// 문제점 - 아예 없을 수도 있기 때문에 continue 걸어 둠
		if (reachedCoordMap[dir].empty())
		{
			dequeEmptyCnt++;
			continue; 
		}

		Util::Coord spawnCoord = reachedCoordMap[dir].front();

		reachedCoordMap[dir].pop_front();

		bool isEnd = reachedCoordMap[dir].empty();

		dirStreamMap[dir][curSpawnIdx]->Spawn(spawnCoord, isEnd);
	}

	if (dequeEmptyCnt >= 4) // 더 이상 spawn시킬 streamBlock이 없음
	{
		stopSpawning = true;
		return;
	}

	curSpawnIdx++;
	
}

void Stream::HandleActive()
{
	for (auto& p : dirStreamMap)
	{
		for (StreamBlock* sb : p.second)
		{
			if (sb->IsActive())
				return;
		}
	}

	// isActive가 모두 꺼진 상태

	isActive = false;
}
