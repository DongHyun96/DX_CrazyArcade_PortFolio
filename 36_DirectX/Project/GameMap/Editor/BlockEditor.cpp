#include "Framework.h"
#include "BlockEditor.h"


BlockEditor::BlockEditor(MapEditor* mapEditor)
	:mapEditor(mapEditor)
{
	InitBlockMaps();

	Load();
}

BlockEditor::~BlockEditor()
{
	Save();
	
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			if (cellBlocks[i][j]) delete cellBlocks[i][j];
		}
	}

	for (auto& p : blockMaps)			delete p.first;
	for (auto& c : blockMapColliders)	delete c;
}

void BlockEditor::Update()
{
	UpdateObjects();

	if (mapEditor->GetMode() != MapEditor::BLOCK_MODE)
		return;

	SelectBlockMap();
	SetBlockToWorld();
}

void BlockEditor::Render()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			if (cellBlocks[i][j]) cellBlocks[i][j]->Render();
		}
	}

	if (mapEditor->GetMode() != MapEditor::BLOCK_MODE)
		return;

	for (auto& block : blockMaps) block.first->Render();

	if (mapEditor->GetRenderColliderFlag())
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

	// BP - BREAKABLE / MOVABLE / HIDABLE

	switch (GM->GetCurMapType())
	{
	case VILLAGE: /*case TEST_FIELD:*/
	{
		Block* block{};
		Collider* collider{};
		BlockInfo info{};

		// Tree
		info = { L"InGame/Village/Objects/tree.png", {0, 0}, {1, 1}, {1, 1}, {false, false, false}, Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW * 1.5f) };
		block = new Block({ 16, 10 }, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp);

		collider = new ColliderRect(CELL_WORLD_SIZE);
		collider->SetParent(block->GetBody());

		blockMaps.push_back({ block, info });
		blockMapColliders.push_back(collider);

		// PushBox
		info = { L"InGame/Village/Objects/Push.png", {0, 0}, {1, 1}, {1, 1}, {true, true, false} };
		block = new Block({ 16, 9 }, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp);

		collider = new ColliderRect(CELL_WORLD_SIZE);
		collider->SetParent(block->GetBody());

		blockMaps.push_back({ block, info });
		blockMapColliders.push_back(collider);

		// House
		for (UINT i = 0; i < 3; i++)
		{
			info = { L"InGame/Village/Objects/house.png", {0, 0}, {3, 1}, {i + 1, 1}, {false, false, false}, Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW * 1.5f) };
			block = new Block({ 16 + i, 12 }, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp);

			collider = new ColliderRect(CELL_WORLD_SIZE);
			collider->SetParent(block->GetBody());

			blockMaps.push_back({ block, info });
			blockMapColliders.push_back(collider);
		}

		// Bush
		for (UINT i = 0; i < 2; i++)
		{
			info = { L"InGame/Village/Objects/Hide.png", {0, 0}, {2, 1}, {i + 1, 1}, {true, false, true},  Vector2(WIN_WIDTH / MAP_COL * 1.15f, WIN_HEIGHT / MAP_ROW) };

			block = new Block({ 17, 10 - i }, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp);

			collider = new ColliderRect(CELL_WORLD_SIZE);
			collider->SetParent(block->GetBody());

			blockMaps.push_back({ block, info });
			blockMapColliders.push_back(collider);
		}

		// 레고블럭들
		for (UINT i = 0; i < 2; i++)
		{
			//block = new Block({ 6, 6 }, L"InGame/Village/Objects/box.png", { 3, 1 }, { 3, 1 }, CELL_WORLD_SIZE, { true, true, false });
			info = { L"InGame/Village/Objects/box.png", {0, 0}, {3, 1}, {i + 1, 1}, {true, false, false} };

			block = new Block({ 17, 8 - i }, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp);

			collider = new ColliderRect(CELL_WORLD_SIZE);
			collider->SetParent(block->GetBody());

			blockMaps.push_back({ block, info });
			blockMapColliders.push_back(collider);
		}

		// Movable Box
		info = { L"InGame/Village/Objects/box.png", {0, 0}, {3, 1}, {3, 1}, {true, true, false} };

		block = new Block({ 17, 6 }, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp);

		collider = new ColliderRect(CELL_WORLD_SIZE);
		collider->SetParent(block->GetBody());

		blockMaps.push_back({ block, info });
		blockMapColliders.push_back(collider);
	}
		break;
	case FOREST:
	{
		Block* block{};
		Collider* collider{};
		BlockInfo info{};

		// 벽돌 1, 2, 3
		for (UINT i = 0; i < 3; i++) // 16, 10 9 8
		{
			info = { L"InGame/Forest/Objects/object"+ to_wstring(i + 1) + L".png", {0, 0}, {1, 1}, {1, 1}, {false, false, false} };

			block = new Block({ 16, 10 - i }, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp);

			collider = new ColliderRect(CELL_WORLD_SIZE);
			collider->SetParent(block->GetBody());

			blockMaps.push_back({ block, info });
			blockMapColliders.push_back(collider);
		}

		// PushBox
		info = { L"InGame/Forest/Objects/block1.png", {0, 0}, {1, 1}, {1, 1}, {true, true, false} };
		block = new Block({ 16, 7 }, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp);

		collider = new ColliderRect(CELL_WORLD_SIZE);
		collider->SetParent(block->GetBody());

		blockMaps.push_back({ block, info });
		blockMapColliders.push_back(collider);

		// 연못
		for (UINT i = 0; i < 6; i++)
		{
			UINT x = i % 3 + 1;
			UINT y = i / 3 + 1;

			info = { L"InGame/Forest/Objects/Deco.png", {0, 0}, {3, 2}, {x, y}, {false, false, false} };

			block = new Block({ 17, 10 - i }, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp);

			collider = new ColliderRect(CELL_WORLD_SIZE);
			collider->SetParent(block->GetBody());

			blockMaps.push_back({ block, info });
			blockMapColliders.push_back(collider);
		}

		// 일반 블록들
		for (UINT i = 0; i < 2; i++) // 18, 10 9 
		{
			info = { L"InGame/Forest/Objects/block" + to_wstring(i + 2) + L".png", {0, 0}, {1, 1}, {1, 1}, {true, false, false} };

			block = new Block({ 18, 10 - i }, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp);

			collider = new ColliderRect(CELL_WORLD_SIZE);
			collider->SetParent(block->GetBody());

			blockMaps.push_back({ block, info });
			blockMapColliders.push_back(collider);
		}
	}
		break;
	case FACTORY:
	{
		Block* block{};
		Collider* collider{};
		BlockInfo info{};

		// 신호등
		info = { L"InGame/Factory/Objects/TrafficLight.png", {0, 0}, {1, 1}, {1, 1}, {false, false, false}, Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW * 2.2f) };
		block = new Block({ 16, 10 }, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp);

		collider = new ColliderRect(CELL_WORLD_SIZE);
		collider->SetParent(block->GetBody());

		blockMaps.push_back({ block, info });
		blockMapColliders.push_back(collider);

		// Arrows
		for (UINT i = 0; i < 2; i++)
		{
			info = { L"InGame/Factory/Objects/Arrows.png", {0, 0}, {2, 1}, {i + 1, 1}, {false, false, false}, Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW * 2.2f) };

			block = new Block({ 17, 8 - i }, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp);

			collider = new ColliderRect(CELL_WORLD_SIZE);
			collider->SetParent(block->GetBody());

			blockMaps.push_back({ block, info });
			blockMapColliders.push_back(collider);
		}

		// Solid Blocks
		for (UINT i = 0; i < 3; i++)
		{
			info = { L"InGame/Factory/Objects/Blocks.png", {0, 0}, {3, 1}, {i + 1, 1}, {false, false, false} };
			block = new Block({ 16 + i, 12 }, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp);

			collider = new ColliderRect(CELL_WORLD_SIZE);
			collider->SetParent(block->GetBody());

			blockMaps.push_back({ block, info });
			blockMapColliders.push_back(collider);
		}


		// Basic 파란색 블록들
		for (UINT i = 0; i < 2; i++)
		{
			info = { L"InGame/Factory/Objects/Basic.bmp", {0, 0}, {2, 1}, {i + 1, 1}, {true, false, false} };

			block = new Block({ 17, 6 - i }, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp);

			collider = new ColliderRect(CELL_WORLD_SIZE);
			collider->SetParent(block->GetBody());

			blockMaps.push_back({ block, info });
			blockMapColliders.push_back(collider);
		}

		// Movables
		for (UINT i = 0; i < 2; i++)
		{
			info = { L"InGame/Factory/Objects/Movable.png", {0, 0}, {2, 1}, {i + 1, 1}, {true, true, false} };

			block = new Block({ 18, 8 - i }, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp);

			collider = new ColliderRect(CELL_WORLD_SIZE);
			collider->SetParent(block->GetBody());

			blockMaps.push_back({ block, info });
			blockMapColliders.push_back(collider);
		}
	}

		break;
	default:
		break;
	}

	


}

void BlockEditor::UpdateObjects()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			if (cellBlocks[i][j]) cellBlocks[i][j]->Update();
		}
	}

	for (auto& block : blockMaps)		block.first->Update();
	for (auto& c : blockMapColliders)	c->Update();
}

void BlockEditor::SelectBlockMap()
{
	UINT idx{};

	for (auto& c : blockMapColliders)
	{
		if (c->OBBCollision(mousePos))
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
			if (mapEditor->cells[i][j]->OBBCollision(mousePos)) // i, j 위치와 info가 필요
			{
				if (KEY_DOWN(VK_LBUTTON))
				{
					CreateBlock({j, i});
					break;
				}
				else if (KEY_DOWN(VK_RBUTTON)) // Eraser
				{
					EraseBlock({ j, i });
					break;
				}
				break;
			}
		}
	}
}

void BlockEditor::CreateBlock(Util::Coord boardXY)
{
	if (cellBlocks[boardXY.y][boardXY.x])
	{
		delete cellBlocks[boardXY.y][boardXY.x];
		cellBlocks[boardXY.y][boardXY.x] = nullptr;
	}

	BlockInfo info = blockMaps[selectedIdx].second;

	info.boardXY = boardXY;

	cellBlocks[boardXY.y][boardXY.x] = new Block(info);
	cellBlocks[boardXY.y][boardXY.x]->SetBoardPos(boardXY);

	infos[boardXY.y][boardXY.x] = info;
}

void BlockEditor::CreateBlock(const BlockInfo& info, Util::Coord boardXY)
{
	if (cellBlocks[boardXY.y][boardXY.x])
	{
		delete cellBlocks[boardXY.y][boardXY.x];
		cellBlocks[boardXY.y][boardXY.x] = nullptr;
	}

	cellBlocks[boardXY.y][boardXY.x] = new Block(info);
	cellBlocks[boardXY.y][boardXY.x]->SetBoardPos(boardXY);

}

void BlockEditor::EraseBlock(const Util::Coord& boardXY)
{
	if (cellBlocks[boardXY.y][boardXY.x])
	{
		delete cellBlocks[boardXY.y][boardXY.x];
		cellBlocks[boardXY.y][boardXY.x] = nullptr;
	}

	infos[boardXY.y][boardXY.x].initialized = false;
}

void BlockEditor::Save()
{
	//GM->tileBinFile[GM->GetCurMapType()]

	BinaryWriter binWriter(GM->blockBinFile[GM->GetCurMapType()]);

	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
			infos[i][j].SaveData(binWriter);
	}
}

void BlockEditor::Load()
{
	// VillageBlockSampleData
	BinaryReader reader(GM->blockBinFile[GM->GetCurMapType()]);

	if (!reader.Succeeded())
		return;

	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			infos[i][j].ReadAndCopy(reader);

			if (infos[i][j].initialized)
				CreateBlock(infos[i][j], { j, i });
		}
	}
}
