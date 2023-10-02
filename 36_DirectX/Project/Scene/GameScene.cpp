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

	//BlockInfo info{};
	//info.file = ""
	//info.boardXY{};
	//info.frameXY{};
	//info.targetXY{};
	//info.bProp{};
	//info.texWorldSize{ CELL_WORLD_SIZE };

	//block = new Block({ 6, 6 }, L"InGame/Village/Objects/box.png", { 3, 1 }, { 3, 1 }, CELL_WORLD_SIZE, { true, true, false });
	curBlockPos = { 6, 6 };
	//block = new Block({ 5, 6 }, L"InGame/Village/Objects/Stone.png", {15, 1}, { 4, 1 }, Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW * 2.f));
	//block = new Block({ 5, 6 }, L"InGame/Village/Objects/tree.png", {1, 1}, {1, 1}, Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW * 1.5f));
	//block = new Block({ 5, 7 }, L"InGame/Village/Objects/house.png", { 3, 1 }, { 2, 1 }, Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW * 1.5f));
	block = new Block({ 5, 6 }, L"InGame/Village/Objects/Hide.png", {2, 1}, {1, 1}, Vector2(WIN_WIDTH / MAP_COL * 1.15f, WIN_HEIGHT / MAP_ROW), {true, false, true});
}

GameScene::~GameScene()
{
	delete mainUI;
	delete mapBoundary;
	delete tileManager;
	delete blockManager;

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
	//blockManager->Update();

	block->Update();

	if (KEY_DOWN(VK_DOWN))
	{
		block->PlayBushInteraction();
	}
	
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
	//blockManager->Render();

	block->Render();
}

//if (KEY_DOWN(VK_LEFT))
//{
//	Util::Coord c = curBlockPos;
//
//	c.x--;
//
//	if (block->Move(c))
//		curBlockPos = c;
//
//}
//else if (KEY_DOWN(VK_RIGHT))
//{
//	Util::Coord c = curBlockPos;
//
//	c.x++;
//
//	if (block->Move(c))
//		curBlockPos = c;
//
//}
//else if (KEY_DOWN(VK_UP))
//{
//	Util::Coord c = curBlockPos;
//
//	c.y++;
//
//	if (block->Move(c))
//		curBlockPos = c;
//
//}
//else if (KEY_DOWN(VK_DOWN))
//{
//	Util::Coord c = curBlockPos;
//
//	c.y--;
//
//	if (block->Move(c))
//		curBlockPos = c;
//}


	