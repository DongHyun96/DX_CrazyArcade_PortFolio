#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{

	/*mapBoundary = new ColliderRect(WIN_SIZE);
	mapBoundary->translation = WIN_CENTER;
	mapBoundary->SetLabel("MapBoundary");*/

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


	player = new Player(BAZZI, P1);
	player->SetLabel("Player");

	GM->SetPlayer(player);

	balloonManager = new BalloonManager;
	GM->SetBalloonManager(balloonManager);

	streamManager = new StreamManager;
	GM->SetStreamManager(streamManager);

	itemManager = new ItemManager;

	dartManager = new DartManager;
	GM->SetDartManager(dartManager);

	//SOUND->Play("VillageBGM", 1.f);
}

GameScene::~GameScene()
{
	//delete mapBoundary;

	delete tileManager;
	delete blockManager;

	/*delete block;
	delete block2;*/

	delete player;
	delete balloonManager;

	delete streamManager;

	delete itemManager;

	delete dartManager;
}

void GameScene::Update()
{
	GM->Update();


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

	itemManager->Update();

	dartManager->Update();
}

void GameScene::Render()
{

	if (GM->IsEditMode())
	{
		MapEditor::GetInst()->Render();
		return;
	}

	tileManager->Render();
	blockManager->Render();
	balloonManager->Render();

	player->Render();
	streamManager->Render();
	itemManager->Render();

	dartManager->Render();
	//player->Debug();
}




	