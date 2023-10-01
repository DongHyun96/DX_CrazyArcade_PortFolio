#include "Framework.h"
#include "BlockEditor.h"


BlockEditor::BlockEditor()
{
	InitBlockMaps();

	Load();
}

BlockEditor::~BlockEditor()
{
	Save();
	
	for (Block* b : cellBlocks)
		delete b;

	for (auto& p : blockMaps)			delete p.first;
	for (auto& c : blockMapColliders)	delete c;
}

void BlockEditor::Update()
{
	UpdateObjects();

	if (MapEditor::GetInst()->GetMode() != MapEditor::BLOCK_MODE)
		return;

	SelectBlockMap();
	SetBlockToWorld();
}

void BlockEditor::Render()
{
	for (Block* b : cellBlocks)
		b->Render();

	if (MapEditor::GetInst()->GetMode() != MapEditor::BLOCK_MODE)
		return;

	for (auto& block : blockMaps)		block.first->Render();
	for (auto& c : blockMapColliders)	c->Render();
}

void BlockEditor::InitBlockMaps()
{
	/*for (UINT i = 0; i < 7; i++)
	{
		TileInfo info{ L"InGame/Village/GroundTiles/Tile.png", 7, 1, i + 1, 1 };
		Object* tile = new Object(CELL_WORLD_SIZE, L"InGame/Village/GroundTiles/Tile.png", 7, 1, i + 1, 1);

		Util::SetTransformToGameBoard(tile, 16, 10 - i);

		Collider* collider = new ColliderRect(CELL_WORLD_SIZE);
		collider->SetParent(tile);

		tileMaps.push_back({ tile, info });
		tileMapColliders.push_back(collider);
	}*/

	//block = new Block({ 6, 6 }, L"InGame/Village/Objects/box.png", { 3, 1 }, { 3, 1 }, CELL_WORLD_SIZE, { true, true, false });
	//block = new Block({ 5, 6 }, L"InGame/Village/Objects/Stone.png", {15, 1}, { 4, 1 }, Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW * 2.f));
	//block = new Block({ 5, 6 }, L"InGame/Village/Objects/tree.png", {1, 1}, {1, 1}, Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW * 1.5f));
	//block = new Block({ 5, 7 }, L"InGame/Village/Objects/house.png", { 3, 1 }, { 2, 1 }, Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW * 1.5f));
	//block = new Block({ 5, 6 }, L"InGame/Village/Objects/Hide.png", {2, 1}, {1, 1}, Vector2(WIN_WIDTH / MAP_COL * 1.15f, WIN_HEIGHT / MAP_ROW), {true, false, true});

	//BlockInfo info{ L"InGame/Village/Objects/tree.png",  }
}

void BlockEditor::UpdateObjects()
{
	for (Block* b : cellBlocks)
		b->Update();

	for (auto& block : blockMaps)		block.first->Update();
	for (auto& c : blockMapColliders)	c->Update();
}

void BlockEditor::SelectBlockMap()
{
	UINT idx{};

	for (auto& c : blockMapColliders)
	{
		if (c->Collision(mousePos))
		{
			if (KEY_DOWN(VK_LBUTTON))
			{
				selectedIdx = idx;
				break;
			}
			break;
		}
		idx++;
	}
}

void BlockEditor::SetBlockToWorld()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			if (MapEditor::GetInst()->cells[i][j]->Collision(mousePos)) // i, j 위치와 info가 필요
			{
				if (KEY_DOWN(VK_LBUTTON))
				{
					CreateBlock({j, i});
					break;
				}
				break;
			}
		}
	}
}

void BlockEditor::CreateBlock(Util::Coord boardXY)
{

}

void BlockEditor::CreateBlock(const BlockInfo& info, Util::Coord boardXY)
{
}

void BlockEditor::Save()
{
}

void BlockEditor::Load()
{
}
