#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	mainUI = new Object(WIN_SIZE, L"InGame/UI/mapToolMap.png");
	mainUI->translation = WIN_CENTER;

	knight = new Knight;

	mapBoundary = new ColliderRect(WIN_SIZE);
	mapBoundary->translation = WIN_CENTER;
	mapBoundary->SetLabel("MapBoundary");

	tileExample = new Object(Vector2(WIN_WIDTH / 15, WIN_HEIGHT / 13), L"InGame/Village/GroundTiles/Tile.png", 7, 1, 4, 1);
	tileExample->translation = Vector2(WIN_WIDTH / 30.f, WIN_HEIGHT / 26.f) - WIN_CENTER;

	tileParentExample = new Transform();
	tileParentExample->scale = Vector2(0.76f, 0.88f);

	tileParentExample->translation = Vector2(768.f, 538.f);
	tileParentExample->SetLabel("TileParent");

	tileExample->SetParent(tileParentExample);

	tileExample->SetLabel("Tile");
	
	for (UINT i = 0; i < MAP_ROW; i++) // ROW
	{
		for (UINT j = 0; j < MAP_COL; j++) // COL
		{
			tileExamples[i][j] = new Object(Vector2(WIN_WIDTH / 15, WIN_HEIGHT / 13), L"InGame/Village/GroundTiles/Tile.png", 7, 1, 4, 1);
			tileExamples[i][j]->translation = Util::ConvertBoardIdxToWorldPos(j, i);
			tileExamples[i][j]->SetParent(tileParentExample);
		}
	}

}

GameScene::~GameScene()
{
	delete mainUI;
	delete knight;
	delete mapBoundary;
	delete tileExample;
	delete tileParentExample;

	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
			delete tileExamples[i][j];
	}

}

void GameScene::Update()
{
	mainUI->Update();
	//knight->Update();
	mapBoundary->Update();

	tileParentExample->Update();
	tileExample->Update();

	for (UINT i = 0; i < 13; i++)
	{
		for (UINT j = 0; j < 15; j++)
			tileExamples[i][j]->Update();
	}
}

void GameScene::Render()
{
	mainUI->Render();
	//knight->Render();
	mapBoundary->Render();

	tileExample->Render();

	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
			tileExamples[i][j]->Render();
	}

	mapBoundary->Debug();
	tileExample->Debug();

	tileParentExample->Debug();
}
