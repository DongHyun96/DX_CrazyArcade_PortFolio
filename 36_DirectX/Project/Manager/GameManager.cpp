#include "Framework.h"
#include "GameManager.h"


GameManager::GameManager()
{

	tileBinFile =
	{
		{VILLAGE, L"VillageTileData"},
		{FACTORY, L""},
		{FOREST, L""}
	}; 

	//VillageBlockSampleData
	blockBinFile =
	{
		{VILLAGE, L"VillageBlockData"},
		{FACTORY, L""},
		{FOREST, L""}
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

	SOUND->AddSound("BalloonDeploy", "_Sound/BalloonDeploy.wav");
	SOUND->AddSound("BalloonExplode", "_Sound/bombExplode.wav");
	SOUND->AddSound("ItemSpawned", "_Sound/ItemGen.mp3");
	SOUND->AddSound("ItemEarned", "_Sound/SetItem.wav");
	SOUND->AddSound("VillageBGM", "_Sound/Boomhill.mp3", true);

	P_DIR_KEYCODE[P1] =
	{
		{DIR_LEFT,	'D'},
		{DIR_RIGHT, 'G'},
		{DIR_UP,	'R'},
		{DIR_DOWN,	'F'}
	};

	P_BALLOON_KEYCODE[P1]	= VK_LSHIFT;
	P_ITEM_KEYCODE[P1]		= VK_LCONTROL;

	P_DIR_KEYCODE[P2] =
	{
		{DIR_LEFT,	VK_LEFT},
		{DIR_RIGHT, VK_RIGHT},
		{DIR_UP,	VK_UP},
		{DIR_DOWN,	VK_DOWN}
	};

	P_BALLOON_KEYCODE[P2]	= VK_RSHIFT;
	P_ITEM_KEYCODE[P2]		= VK_HANJA;
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
	if (KEY_DOWN(VK_ESCAPE))
		PostQuitMessage(0);

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

void GameManager::SetGameMode(const GameMode& gameMode)
{
	switch (gameMode)
	{
	case PVP:
		P_DIR_KEYCODE[P1] =
		{
			{DIR_LEFT,	'D'},
			{DIR_RIGHT, 'G'},
			{DIR_UP,	'R'},
			{DIR_DOWN,	'F'}
		};

		P_BALLOON_KEYCODE[P1] = VK_LSHIFT;
		P_ITEM_KEYCODE[P1] = VK_LCONTROL;

		break;
	case PVE:
		P_DIR_KEYCODE[P1] =
		{
			{DIR_LEFT,	VK_LEFT},
			{DIR_RIGHT, VK_RIGHT},
			{DIR_UP,	VK_UP},
			{DIR_DOWN,	VK_DOWN}
		};

		P_BALLOON_KEYCODE[P1] = VK_SPACE;
		P_ITEM_KEYCODE[P1] = VK_LCONTROL;

		break;
	default:
		break;
	}

	this->gameMode = gameMode;
}

void GameManager::SetPlayers(Character* p1, Character* p2)
{
	this->p1 = p1;
	this->p2 = p2;

	wholePlayers.clear();

	wholePlayers.push_back(p1);
	wholePlayers.push_back(p2);
}

void GameManager::SetPlayers(Character* p1, vector<Character*> enemies)
{
	this->p1 = p1;
	this->comEnemies = enemies;

	wholePlayers.clear();

	wholePlayers = enemies;
	wholePlayers.push_back(p1);
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

