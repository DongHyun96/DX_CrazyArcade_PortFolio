#include "Framework.h"
#include "TileEditor.h"


TileEditor::TileEditor(MapEditor* mapEditor)
	:mapEditor(mapEditor)
{
	InitTileButtons();

	Load();
}

TileEditor::~TileEditor()
{
	Save();

	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			if (cellTiles[i][j])
				delete cellTiles[i][j];
		}
	}

	for (auto& tile : tileMaps)		 delete tile.first;
	for (auto& c : tileMapColliders) delete c;
}


void TileEditor::Update()
{
	UpdateObjects();

	if (mapEditor->GetMode() != MapEditor::TILE_MODE)
		return;

	SelectTileMap();
	HandleSetTileToWorld();
}

void TileEditor::Render()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			if (cellTiles[i][j]) cellTiles[i][j]->Render();
		}
	}

	if (mapEditor->GetMode() != MapEditor::TILE_MODE)
		return;

	for (auto& tile : tileMaps) tile.first->Render();

	if (mapEditor->GetRenderColliderFlag())
		for (auto& c : tileMapColliders) c->Render();
}

void TileEditor::UpdateObjects()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			if (cellTiles[i][j]) cellTiles[i][j]->Update();
		}
	}

	for (auto& tile : tileMaps)		 tile.first->Update();
	for (auto& c : tileMapColliders) c->Update();
}


void TileEditor::InitTileButtons()
{
	switch (GM->GetCurMapType())
	{
	case VILLAGE: /*case TEST_FIELD:*/
		for (UINT i = 0; i < 7; i++)
		{
			TileInfo info{ L"InGame/Village/GroundTiles/Tile.png", 7, 1, i + 1, 1 };
			Object* tile = new Object(CELL_WORLD_SIZE, L"InGame/Village/GroundTiles/Tile.png", 7, 1, i + 1, 1);

			Util::SetTransformToGameBoard(tile, 16, 10 - i);

			Collider* collider = new ColliderRect(CELL_WORLD_SIZE);
			collider->SetParent(tile);

			tileMaps.push_back({ tile, info });
			tileMapColliders.push_back(collider);
		}

		for (UINT i = 0; i < 5; i++)
		{
			TileInfo info{ L"InGame/Village/GroundTiles/Tile2.bmp", 5, 1, i + 1, 1 };
			Object* tile = new Object(CELL_WORLD_SIZE, L"InGame/Village/GroundTiles/Tile2.bmp", 5, 1, i + 1, 1);

			Util::SetTransformToGameBoard(tile, 17, 10 - i);

			Collider* collider = new ColliderRect(CELL_WORLD_SIZE);
			collider->SetParent(tile);

			tileMaps.push_back({ tile, info });
			tileMapColliders.push_back(collider);
		}
		break;
	case FOREST:
	{
		for (UINT i = 0; i < 6; i++)
		{
			TileInfo info{ L"InGame/Forest/Tiles/tile" + to_wstring(5 + i) + L".bmp" };
			Object* tile = new Object(CELL_WORLD_SIZE, L"InGame/Forest/Tiles/tile" + to_wstring(5 + i) + L".bmp");

			Util::SetTransformToGameBoard(tile, 16, 10 - i);

			Collider* collider = new ColliderRect(CELL_WORLD_SIZE);
			collider->SetParent(tile);

			tileMaps.push_back({ tile, info });
			tileMapColliders.push_back(collider);
		}
	}
	case FACTORY:
		for (UINT i = 0; i < 5; i++)
		{
			TileInfo info{ L"InGame/Factory/Tiles/Tile.bmp", 15, 1, i + 1, 1 };
			Object* tile = new Object(CELL_WORLD_SIZE, L"InGame/Factory/Tiles/Tile.bmp", 15, 1, i + 1, 1);

			Util::SetTransformToGameBoard(tile, 16, 10 - i);

			Collider* collider = new ColliderRect(CELL_WORLD_SIZE);
			collider->SetParent(tile);

			tileMaps.push_back({ tile, info });
			tileMapColliders.push_back(collider);
		}
		break;
	default:
		break;
	}
	

}

void TileEditor::SelectTileMap()
{
	UINT idx{};
	for (auto& tMapC : tileMapColliders)
	{
		if (tMapC->OBBCollision(mousePos))
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

void TileEditor::HandleSetTileToWorld()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			if (mapEditor->cellColliders[i][j]->OBBCollision(mousePos)) // i, j 위치와 info가 필요
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

void TileEditor::CreateTile(UINT boardX, UINT boardY)
{
	if (cellTiles[boardY][boardX])
	{
		delete cellTiles[boardY][boardX];
		cellTiles[boardY][boardX] = nullptr;
	}

	TileInfo curInfo = tileMaps[selectedTIdx].second;

	cellTiles[boardY][boardX] = new Object(CELL_WORLD_SIZE, curInfo.file, curInfo.frameX, curInfo.frameY, curInfo.targetX, curInfo.targetY);

	Util::SetTransformToGameBoard(cellTiles[boardY][boardX], boardX, boardY);

	cellTiles[boardY][boardX]->zDepth = FAR_Z - 10.f;

	infos[boardY][boardX] = tileMaps[selectedTIdx].second;


}

void TileEditor::CreateTile(const TileInfo& info, UINT boardX, UINT boardY)
{
	if (cellTiles[boardY][boardX])
	{
		delete cellTiles[boardY][boardX];
		cellTiles[boardY][boardX] = nullptr;
	}

	cellTiles[boardY][boardX] = new Object(CELL_WORLD_SIZE, info.file, info.frameX, info.frameY, info.targetX, info.targetY);

	Util::SetTransformToGameBoard(cellTiles[boardY][boardX], boardX, boardY);

	cellTiles[boardY][boardX]->zDepth = FAR_Z - 10.f;

}


void TileEditor::Save()
{
	BinaryWriter binWriter(GM->tileBinFile[GM->GetCurMapType()]);

	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
			infos[i][j].SaveData(binWriter);
	}
}

void TileEditor::Load()
{
	BinaryReader reader(GM->tileBinFile[GM->GetCurMapType()]);

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