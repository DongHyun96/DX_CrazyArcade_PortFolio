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
}

GameManager::~GameManager()
{
	delete gameFieldTransform;
}

void GameManager::Update()
{
	gameFieldTransform->Update();
}
