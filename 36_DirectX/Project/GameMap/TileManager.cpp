#include "Framework.h"
#include "TileManager.h"

TileManager::TileManager()
{
	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
			CreateTile(x, y, L"InGame/Village/GroundTiles/Tile.png", 7, 1, 4, 1);
	}

}

TileManager::~TileManager()
{
	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
		{
			if (tiles[y][x])
				delete tiles[y][x];
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

void TileManager::CreateTile(UINT boardX, UINT boardY, wstring file, UINT frameX, UINT frameY, UINT targetX, UINT targetY, Vector2 size)
{

	assert(!tiles[boardY][boardX]);

	tiles[boardY][boardX] = new Object(size, file, frameX, frameY, targetX, targetY);

	Util::SetTransformToGameBoard(tiles[boardY][boardX], boardX, boardY);
	tiles[boardY][boardX]->zDepth = FAR_Z - 10;
}
