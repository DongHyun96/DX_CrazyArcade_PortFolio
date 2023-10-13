#include "Framework.h"
#include "BlockManager.h"

Block* BlockManager::blocks[MAP_ROW][MAP_COL]{};


BlockManager::BlockManager()
{

	//block = new Block({ 6, 6 }, L"InGame/Village/Objects/box.png", { 3, 1 }, { 3, 1 }, CELL_WORLD_SIZE, { true, true, false });

	/*for (UINT y = 5; y <= 9; y += 2)
	{
		for (UINT x = 5; x < 8; x++)
			CreateBlock({ x, y }, L"InGame/Village/Objects/box.png", {3, 1}, {2, 1}, CELL_WORLD_SIZE, {true, false, false});
	}*/

	Load();
}

BlockManager::~BlockManager()
{

	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
			if (blocks[y][x]) delete blocks[y][x];
	}
}

void BlockManager::Update()
{
	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
			if (blocks[y][x]) blocks[y][x]->Update();
	}

	HandleCommonCollisions();
	HandleHidableCollisions();
	HandleMovableCollisions();
}


void BlockManager::Render()
{
	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
			if (blocks[y][x]) blocks[y][x]->Render();
	}
}

void BlockManager::SwapBlocks(const Util::Coord& c1, const Util::Coord& c2)
{
	Util::Swap(blocks[c1.y][c1.x], blocks[c2.y][c2.x]);
}

bool BlockManager::IsValidDestCoord(const Util::Coord& dest)
{
	if (dest.x < 0 || dest.x >= MAP_COL || dest.y < 0 || dest.y >= MAP_ROW) return false;

	if (!blocks[dest.y][dest.x]) return true;

	if (!blocks[dest.y][dest.x]->IsActive()) return true;

	if (blocks[dest.y][dest.x]->IsHidable()) return true;


	return false;
}

Block* BlockManager::CreateBlock(Util::Coord coord, wstring file, Util::Coord frameXY, Util::Coord targetXY, Vector2 texWorldSize, BlockProperty bProp)
{
	assert(!blocks[coord.y][coord.x]);

	blocks[coord.y][coord.x] = new Block(coord, file, frameXY, targetXY, texWorldSize, bProp);
	blocks[coord.y][coord.x]->SetBoardPos({ coord.x, coord.y });

	return blocks[coord.y][coord.x];
}

Block* BlockManager::CreateBlock(const BlockInfo& info, Util::Coord boardXY)
{
	blocks[boardXY.y][boardXY.x] = new Block(info);
	blocks[boardXY.y][boardXY.x]->SetBoardPos(boardXY);

	return blocks[boardXY.y][boardXY.x];
}

void BlockManager::Load()
{
	// VillageBlockData
	//VillageBlockSampleData
	BinaryReader reader(L"VillageBlockData");

	if (!reader.Succeeded())
		return;

	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			infos[i][j].ReadAndCopy(reader);

			if (infos[i][j].initialized)
			{
				Block* created = CreateBlock(infos[i][j], { j, i });

				if (created->IsMovable()) movableBlocks.push_back(created);
				else if (created->IsHidable()) hidableBlocks.push_back(created);
			}
		}
	}
}

void BlockManager::HandleCommonCollisions()
{
	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
		{
			if (!blocks[y][x]) continue;
			if (!blocks[y][x]->IsActive()) continue;

			HandleCharacterCommonCollision(blocks[y][x]);
			HandleDartCollision(blocks[y][x]);
		}
	}
}

void BlockManager::HandleCharacterCommonCollision(Block* block)
{
	ColliderHolder* character = (ColliderHolder*)(GM->GetPlayer());

	block->GetBody()->AABBCollision(GM->GetPlayer()->GetBody(), character);
	block->GetBody()->AABBCollision(GM->GetPlayer()->GetBody()->GlobalPosition(), character);
}

void BlockManager::HandleDartCollision(Block* block)
{
	for (Dart* dart : GM->GetDartManager()->GetDarts())
	{
		if (!dart->GetIsActive()) continue;

		if (block->IsHidable()) continue; // Hidable을 제외한 블록들에 dart가 맞으면 dart 끔

		if (block->GetBody()->AABBCollision(dart->GetBody()))
			dart->SetActive(false);
	}
}



void BlockManager::HandleMovableCollisions()
{
	for (Block* movable : movableBlocks)
	{
		if (!movable->IsActive())
			continue;

		// Player vs movable
		movable->GetBody()->AABBCollision(GM->GetPlayer()->GetPushCollider(), (ColliderHolder*)(GM->GetPlayer()));
	}
}

void BlockManager::HandleHidableCollisions()
{
	for (Block* hidable : hidableBlocks)
	{
		if (!hidable->IsActive())
			continue;

		// vs movables
		for (Block* movable : movableBlocks)
		{
			if (!movable->IsActive())
				continue;

			hidable->GetBody()->AABBCollision(movable->GetBody()->GlobalPosition(), movable);

		}

		// vs Balloons
		for (Balloon* balloon : GM->GetBalloonManager()->GetNormalBalloons()) // 일반 벌룬들
		{
			if (!balloon->Active())
				continue;

			hidable->GetBody()->AABBCollision(balloon->GetBody()->GlobalPosition(), (ColliderHolder*)balloon);
		}

		for (TimerBalloon* balloon : GM->GetBalloonManager()->GetTimerBalloons())
		{
			if (!balloon->Active())
				continue;

			hidable->GetBody()->AABBCollision(balloon->GetBody()->GlobalPosition(), (ColliderHolder*)balloon);
		}
	}
}

