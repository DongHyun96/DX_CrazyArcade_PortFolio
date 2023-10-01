#include "Framework.h"
#include "BlockManager.h"


BlockManager::BlockManager()
{
	destroyedAnim = new Animation(L"InGame/BlockDestroyedSprite/common_block.png", 4, 1, 4, 1.f);
	destroyedAnim->SetAll(false);

	//block = new Block({ 6, 6 }, L"InGame/Village/Objects/box.png", { 3, 1 }, { 3, 1 }, CELL_WORLD_SIZE, { true, true, false });

	for (UINT i = 3; i < MAP_ROW; i++)
	{
		for (UINT j = 3; j < MAP_COL; j++)
			CreateBlock({ j, i }, L"InGame/Village/Objects/box.png", { 3, 1 }, { 2, 1}, CELL_WORLD_SIZE, {true, false, false});
	}
}

BlockManager::~BlockManager()
{
	delete destroyedAnim;

	for (Block* b : blocks)
		delete b;
}

void BlockManager::Update()
{
	for (Block* block : blocks)
		block->Update();
}

void BlockManager::Render()
{
	for (Block* block : blocks)
		block->Render();
}

void BlockManager::CreateBlock(Util::Coord coord, wstring file, Util::Coord frameXY, Util::Coord targetXY, Vector2 texWorldSize, BlockProperty bProp)
{
	blocks.push_back(new Block(coord, file, frameXY, targetXY, texWorldSize, bProp));
}



//if (KEY_DOWN(VK_LEFT))
	//{
	//	Util::Coord c = block->GetBoardPos();

	//	c.x--;

	//	block->Move(c);
	//	
	//}
	//else if (KEY_DOWN(VK_RIGHT))
	//{
	//	Util::Coord c = block->GetBoardPos();

	//	c.x++;

	//	block->Move(c);

	//}
	//else if (KEY_DOWN(VK_UP))
	//{
	//	Util::Coord c = block->GetBoardPos();

	//	c.y++;

	//	block->Move(c);

	//}
	//else if (KEY_DOWN(VK_DOWN))
	//{
	//	Util::Coord c = block->GetBoardPos();

	//	c.y--;

	//	block->Move(c);
	//}

	////if (KEY_DOWN(VK_DOWN))
	////{
	////	block->PlayBushInteraction();
	////}