#include "Framework.h"
#include "GameManager.h"


GameManager::GameManager()
{
	gameFieldTransform = new Transform;

	gameFieldTransform->scale = Vector2(0.76f, 0.88f);
	gameFieldTransform->translation = Vector2(768.f, 538.f);

	Vector2 LT = Util::ConvertBoardIdxToWorldPos(0, MAP_ROW - 1);
	Vector2 RB = Util::ConvertBoardIdxToWorldPos(MAP_COL - 1, 0);
	
	mapL = LT.x - CELL_WORLD_SIZE.x * 0.5f;
	mapT = LT.y + CELL_WORLD_SIZE.y * 0.5f;
	mapR = RB.x + CELL_WORLD_SIZE.x * 0.5f;
	mapB = RB.y - CELL_WORLD_SIZE.y * 0.5f;

	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
		{
			mapCells[y][x] = new ColliderRect(CELL_WORLD_SIZE);
		}
	}

	SOUND->AddSound("BalloonDeploy", "_Sound/BalloonDeploy.wav");
}

GameManager::~GameManager()
{
	delete gameFieldTransform;

	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
			delete mapCells[y][x];
	}
}

void GameManager::Update()
{
	gameFieldTransform->Update();

	static bool cellInitialized = false;

	if (!cellInitialized)
	{
		for (UINT y = 0; y < MAP_ROW; y++)
		{
			for (UINT x = 0; x < MAP_COL; x++)
				Util::SetTransformToGameBoard(mapCells[y][x], { x, y });
		}
		cellInitialized = true;
	}


	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
			mapCells[y][x]->Update();
	}
}

Vector2 GameManager::GetCollidedMapCellPos(const Vector2& point)
{
	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
		{
			if (mapCells[y][x]->AABBCollision(point))
				return mapCells[y][x]->translation;
		}
	}

	return Vector2();
}

Util::Coord GameManager::GetCollidedMapCellCoord(const Vector2& point)
{
	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
		{
			if (mapCells[y][x]->AABBCollision(point)) return { x, y };
		}
	}

	return Util::Coord();
}

