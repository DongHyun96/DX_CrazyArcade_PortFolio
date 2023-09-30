#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	mainUI = new Object(WIN_SIZE, L"InGame/UI/mapToolMap.png");
	mainUI->translation = WIN_CENTER;

	mapBoundary = new ColliderRect(WIN_SIZE);
	mapBoundary->translation = WIN_CENTER;
	mapBoundary->SetLabel("MapBoundary");

	tileManager = new TileManager;

	//block = new Block({ 5, 6 }, L"InGame/Village/Objects/box.png", { 3, 1 }, { 2, 1 });
	block = new Block({ 5, 6 }, L"InGame/Village/Objects/Stone.png", {15 , 1 }, { 4, 1 }, Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW * 2.f));
	//block = new Block({ 5, 6 }, L"InGame/Village/Objects/bush.png");

}

GameScene::~GameScene()
{
	delete mainUI;
	delete mapBoundary;
	delete tileManager;
	delete block;
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

	block->Update();
}

void GameScene::Render()
{

	mainUI->Render();

	if (GM->IsEditMode())
	{
		MapEditor::GetInst()->Render();
		return;
	}

	//tileManager->Render();
	block->Render();

}
