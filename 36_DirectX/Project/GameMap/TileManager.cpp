#include "Framework.h"
#include "TileManager.h"

TileManager::TileManager()
{
	Load();
}

TileManager::~TileManager()
{
	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
		{
			if (tiles[y][x])
			{
				delete tiles[y][x];
				tiles[y][x] = nullptr;
			}
		}
	}
}

void TileManager::Update()
{
	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
		{
			if (tiles[y][x])
				tiles[y][x]->Update();
		}
	}
}

void TileManager::Render()
{
	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
		{
			if (tiles[y][x])
				tiles[y][x]->Render();
		}
	}
}

void TileManager::CreateTile(const TileInfo& info, UINT boardX, UINT boardY)
{
	tiles[boardY][boardX] = new Object(CELL_WORLD_SIZE, info.file, info.frameX, info.frameY, info.targetX, info.targetY);

	Util::SetTransformToGameBoard(tiles[boardY][boardX], boardX, boardY);

	tiles[boardY][boardX]->zDepth = FAR_Z - 10.f;
}

void TileManager::Load()
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
