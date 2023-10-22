#include "Framework.h"
#include "GameManager.h"

GameManager::GameManager()
{

	tileBinFile =
	{
		{VILLAGE, L"VillageTileData"},
		{FACTORY, L"FactoryTileData"},
		{FOREST, L"ForestTileData"},
		{TEST_FIELD, L"VillageTileData"}
	}; 

	// VillageBlockData
	blockBinFile =
	{
		{VILLAGE, L"VillageBlockData"},
		{FACTORY, L"FactoryBlockData"},
		{FOREST, L"ForestBlockData"},
		{TEST_FIELD, L"VillageBlockSampleData"}
	};

	mapBGM =
	{
		{VILLAGE, "VillageBGM"},
		{FACTORY, "FactoryBGM"},
		{FOREST, "ForestBGM"},
		{TEST_FIELD, "VillageBGM"}
	};

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

	pSelectedCharacterMap =
	{
		{P1, BAZZI},
		{P2, BAZZI}
	};
}

GameManager::~GameManager()
{
	delete gameFieldTransform;

	for (UINT y = 0; y < MAP_ROW; y++)
	{
		for (UINT x = 0; x < MAP_COL; x++)
			delete mapCells[y][x];
	}

	delete gameUIManager;

	delete playerManager;

	delete balloonManager;

	delete streamManager;

	if (itemManager)
	{
		delete itemManager;
		itemManager = nullptr;
	}

	delete dartManager;

	/*
	GameScene* gameScene{};

	GameUIManager* gameUIManager{};

	PlayerManager* playerManager{};

	// 타일매니저와 BlockManager는 늘상 바뀜 (GameScene에서 생성 해제 담당), BlockManager만 GameManager로 set해서 전역으로 뿌릴 것임
	BlockManager* blockManager{}; 

	BalloonManager* balloonManager{};

	StreamManager* streamManager{};

	ItemManager* itemManager{};

	DartManager* dartManager{};
	*/
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

void GameManager::CreateGameObjects()
{
	playerManager	= new PlayerManager;
	balloonManager	= new BalloonManager;
	streamManager	= new StreamManager;
	itemManager		= new ItemManager;
	dartManager		= new DartManager;
	gameUIManager	= new GameUIManager;
}

void GameManager::InitGame()
{
	gameUIManager->Init();

	playerManager->Init();

	balloonManager->Init();

	streamManager->Init();

	itemManager->Init();

	dartManager->Init();

	gameStatus = START;
}

