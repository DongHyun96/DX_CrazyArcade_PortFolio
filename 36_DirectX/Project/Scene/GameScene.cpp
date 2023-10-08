#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	mainUI = new Object(WIN_SIZE, L"InGame/UI/mapToolMap.png");
	mainUI->translation = WIN_CENTER;
	mainUI->zDepth = FAR_Z - 1;

	mapBoundary = new ColliderRect(WIN_SIZE);
	mapBoundary->translation = WIN_CENTER;
	mapBoundary->SetLabel("MapBoundary");

	tileManager = new TileManager;

	blockManager = new BlockManager;
	GM->SetBlockManager(blockManager);

	//BlockInfo info{};
	//info.file = ""
	//info.boardXY{};
	//info.frameXY{};
	//info.targetXY{};
	//info.bProp{};
	//info.texWorldSize{ CELL_WORLD_SIZE };

	// Breakable, movable hidable
	//block = new Block({ 5, 6 }, L"InGame/Village/Objects/Stone.png", {15, 1}, { 4, 1 }, Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW * 2.f));
	//block = new Block({ 5, 6 }, L"InGame/Village/Objects/tree.png", {1, 1}, {1, 1}, Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW * 1.5f));
	//block = new Block({ 5, 7 }, L"InGame/Village/Objects/house.png", { 3, 1 }, { 2, 1 }, Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW * 1.5f));
	/*block = new Block({ 5, 6 }, L"InGame/Village/Objects/Hide.png", {2, 1}, {1, 1}, Vector2(WIN_WIDTH / MAP_COL * 1.15f, WIN_HEIGHT / MAP_ROW), {true, false, true});
	block2 = new Block({ 5, 2 }, L"InGame/Village/Objects/box.png", { 3, 1 }, { 2, 1 }, CELL_WORLD_SIZE, { true, false, false });
	curBlockPos = { 7, 6 };*/


	player = new Player(BAZZI);
	player->SetLabel("Player");

	GM->SetPlayer(player);

	balloonManager = new BalloonManager;
	GM->SetBalloonManager(balloonManager);

	streamManager = new StreamManager;
}

GameScene::~GameScene()
{
	delete mainUI;
	delete mapBoundary;
	delete tileManager;
	delete blockManager;

	/*delete block;
	delete block2;*/

	delete player;
	delete balloonManager;

	delete streamManager;

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

		
	player->Update();

	tileManager->Update();
	blockManager->Update();
	balloonManager->Update();

	streamManager->Update();

	if (KEY_DOWN(VK_F3))
		streamManager->Spawn({ 6, 7 }, 1);
}

void GameScene::Render()
{

	mainUI->Render();

	if (GM->IsEditMode())
	{
		MapEditor::GetInst()->Render();
		return;
	}

	streamManager->Render();

	tileManager->Render();
	//blockManager->Render();
	balloonManager->Render();

	/*block->Render();
	block2->Render();*/
	player->Render();

	player->Debug();
	//block2->Debug("Block2");
}




	