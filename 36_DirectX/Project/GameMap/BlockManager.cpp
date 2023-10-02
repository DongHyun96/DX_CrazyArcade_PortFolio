#include "Framework.h"
#include "BlockManager.h"


BlockManager::BlockManager()
{
	destroyedAnim = new Animation(L"InGame/BlockDestroyedSprite/common_block.png", 4, 1, 4, 1.f);
	destroyedAnim->SetAll(false);

	//block = new Block({ 6, 6 }, L"InGame/Village/Objects/box.png", { 3, 1 }, { 3, 1 }, CELL_WORLD_SIZE, { true, true, false });

	for (UINT y = 3; y < MAP_ROW; y++)
	{
		for (UINT x = 3; x < MAP_COL; x++)
			CreateBlock({ x, y }, L"InGame/Village/Objects/box.png", { 3, 1 }, {2, 1}, CELL_WORLD_SIZE, {true, false, false});
	}
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
}


void BlockManager::Render()
{
	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
			if (blocks[y][x]) blocks[y][x]->Render();
	}
}

void BlockManager::CreateBlock(Util::Coord coord, wstring file, Util::Coord frameXY, Util::Coord targetXY, Vector2 texWorldSize, BlockProperty bProp)
{
	assert(!blocks[coord.y][coord.x]);

	blocks[coord.y][coord.x] = new Block(coord, file, frameXY, targetXY, texWorldSize, bProp);
}

