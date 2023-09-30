#include "Framework.h"
#include "MapEditor.h"


MapEditor::MapEditor()
{
	InitCells();
	InitTileMaps();

	Load();
}

MapEditor::~MapEditor()
{
	Save();

	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			delete cells[i][j];

			if (cellTiles[i][j])
				delete cellTiles[i][j];
		}
	}

	for (auto& tile : tileMaps)		 delete tile.first;
	for (auto& c : tileMapColliders) delete c;

}


void MapEditor::Update()
{
	UpateObjects();

	SelectTileMap();

	SetTileToWorld();

}

void MapEditor::Render()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			if (cellTiles[i][j]) cellTiles[i][j]->Render();
			cells[i][j]->Render();
		}
	}

	for (auto& tile : tileMaps)		 tile.first->Render();
	for (auto& c : tileMapColliders) c->Render();
}

void MapEditor::UpateObjects()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			if (cellTiles[i][j]) cellTiles[i][j]->Update();
			cells[i][j]->Update();
		}
	}

	for (auto& tile : tileMaps)		 tile.first->Update();
	for (auto& c : tileMapColliders) c->Update();
}

void MapEditor::InitCells()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			cells[i][j] = new ColliderRect(cellSize);
			cells[i][j]->translation = Util::ConvertBoardIdxToWorldPos(j, i);
			cells[i][j]->SetParent(GM->GetGameFieldTransform());
		}
	}
}

void MapEditor::InitTileMaps()
{
	for (UINT i = 0; i < 7; i++)
	{
		TileInfo info{ L"InGame/Village/GroundTiles/Tile.png", 7, 1, i + 1, 1 };
		Object* tile = new Object(cellSize, L"InGame/Village/GroundTiles/Tile.png", 7, 1, i + 1, 1);

		tile->translation = Util::ConvertBoardIdxToWorldPos(16, 10 - i);
		tile->SetParent(GM->GetGameFieldTransform());

		Collider* collider = new ColliderRect(cellSize);
		collider->SetParent(tile);

		tileMaps.push_back({ tile, info });
		tileMapColliders.push_back(collider);
	}

	for (UINT i = 0; i < 5; i++)
	{
		TileInfo info{ L"InGame/Village/GroundTiles/Tile2.bmp", 5, 1, i + 1, 1 };
		Object* tile = new Object(cellSize, L"InGame/Village/GroundTiles/Tile2.bmp", 5, 1, i + 1, 1);

		tile->translation = Util::ConvertBoardIdxToWorldPos(17, 10 - i);
		tile->SetParent(GM->GetGameFieldTransform());

		Collider* collider = new ColliderRect(cellSize);
		collider->SetParent(tile);

		tileMaps.push_back({ tile, info });
		tileMapColliders.push_back(collider);
	}
	
}

void MapEditor::SelectTileMap()
{
	UINT idx{};
	for (auto& tMapC : tileMapColliders)
	{
		if (tMapC->Collision(mousePos))
		{
			if (KEY_DOWN(VK_LBUTTON))
			{
				selectedTIdx = idx;
				break;
			}
			break;
		}
		idx++;
	}
}

void MapEditor::SetTileToWorld()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			if (cells[i][j]->Collision(mousePos)) // i, j 위치와 info가 필요
			{
				if (KEY_DOWN(VK_LBUTTON))
				{
					CreateTile(j, i);
					break;
				}
				break;
			}
		}
	}
}

void MapEditor::CreateTile(UINT boardX, UINT boardY)
{
	if (cellTiles[boardY][boardX])
	{
		delete cellTiles[boardY][boardX];
		cellTiles[boardY][boardX] = nullptr;
	}

	TileInfo curInfo = tileMaps[selectedTIdx].second;

	cellTiles[boardY][boardX] = new Object(cellSize, curInfo.file, curInfo.frameX, curInfo.frameY, curInfo.targetX, curInfo.targetY);

	cellTiles[boardY][boardX]->translation = Util::ConvertBoardIdxToWorldPos(boardX, boardY);
	cellTiles[boardY][boardX]->SetParent(GM->GetGameFieldTransform());

	infos[boardY][boardX] = tileMaps[selectedTIdx].second;
}

void MapEditor::CreateTile(const TileInfo& info, UINT boardX, UINT boardY)
{
	if (cellTiles[boardY][boardX])
	{
		delete cellTiles[boardY][boardX];
		cellTiles[boardY][boardX] = nullptr;
	}

	cellTiles[boardY][boardX] = new Object(cellSize, info.file, info.frameX, info.frameY, info.targetX, info.targetY);

	cellTiles[boardY][boardX]->translation = Util::ConvertBoardIdxToWorldPos(boardX, boardY);
	cellTiles[boardY][boardX]->SetParent(GM->GetGameFieldTransform());
}


void MapEditor::Save()
{
	BinaryWriter binWriter(L"VillageTileData");

	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
			infos[i][j].SaveData(binWriter);
	}
}

void MapEditor::Load()
{
	BinaryReader reader(L"VillageTileData");

	if (!reader.Succeeded())
		return;

	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			infos[i][j].ReadAndCopy(reader);
			CreateTile(infos[i][j], j, i);
		}
	}
}
