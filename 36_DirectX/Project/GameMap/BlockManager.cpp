#include "Framework.h"
#include "BlockManager.h"

Block* BlockManager::blocks[MAP_ROW][MAP_COL]{};


BlockManager::BlockManager()
{
	destroyedAnim = new Animation(L"InGame/BlockDestroyedSprite/common_block.png", 4, 1, 4, 1.f);
	destroyedAnim->SetAll(false);

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
	delete destroyedAnim;

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

	HandleCharacterBlockCollision();
	HandleMovableHidableCollision();
	HandleCharacterMovableCollision();
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
	BinaryReader reader(L"VillageBlockSampleData");

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

void BlockManager::HandleCharacterBlockCollision()
{
	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
		{
			if (blocks[y][x])
			{
				if (!blocks[y][x]->IsActive())
					continue;

				Transform* character = (Transform*)(GM->GetPlayer());

				blocks[y][x]->GetBody()->Collision(GM->GetPlayer()->GetBody(), character);
				blocks[y][x]->GetBody()->Collision(GM->GetPlayer()->GetBody()->GlobalPosition(), character);
			}
		}
	}
}

void BlockManager::HandleCharacterMovableCollision()
{
	for (Block* movable : movableBlocks)
	{
		if (!movable->IsActive())
			continue;

		movable->GetBody()->Collision(GM->GetPlayer()->GetPushCollider(), (Transform*)(GM->GetPlayer()));
	}
}

void BlockManager::HandleMovableHidableCollision()
{
	for (Block* movable : movableBlocks)
	{
		if (!movable->IsActive())
			continue;

		for (Block* hidable : hidableBlocks)
		{
			if (!hidable->IsActive())
				continue;

			hidable->GetBody()->Collision(movable->GetBody()->GlobalPosition(), movable);
		}
	}
}

