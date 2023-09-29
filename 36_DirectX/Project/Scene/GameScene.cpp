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

	tileManager = new TileManager;
}

GameScene::~GameScene()
{
	delete mainUI;
	delete knight;
	delete mapBoundary;
	delete tileManager;

}

void GameScene::Update()
{
	GM->Update();

	mainUI->Update();
	//knight->Update();
	mapBoundary->Update();

	tileManager->Update();
}

void GameScene::Render()
{
	mainUI->Render();
	//knight->Render();
	mapBoundary->Render();
	
	tileManager->Render();

	mapBoundary->Debug();
}
