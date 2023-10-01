#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	mainUI = new Object(WIN_SIZE, L"InGame/UI/mapToolMap.png");
	mainUI->translation = WIN_CENTER;
	mainUI->zDepth = 1300.f;

	mapBoundary = new ColliderRect(WIN_SIZE);
	mapBoundary->translation = WIN_CENTER;
	mapBoundary->SetLabel("MapBoundary");

	tileManager = new TileManager;
	blockManager = new BlockManager;

}

GameScene::~GameScene()
{
	delete mainUI;
	delete mapBoundary;
	delete tileManager;
	delete blockManager;
}

void GameScene::Update()
{
	GM->Update();

	mainUI->Update();

	if (GM->IsEditMode())
	{
		MapEditor::GetInst()->Update();
		return;
	}

	tileManager->Update();
	blockManager->Update();
	
}

void GameScene::Render()
{

	mainUI->Render();

	if (GM->IsEditMode())
	{
		MapEditor::GetInst()->Render();
		return;
	}

	tileManager->Render();
	blockManager->Render();

}
