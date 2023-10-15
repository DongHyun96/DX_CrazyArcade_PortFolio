#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	tileManager = new TileManager;

	playerManager = new PlayerManager;
	GM->SetPlayerManager(playerManager);

	blockManager = new BlockManager;
	GM->SetBlockManager(blockManager);

	balloonManager = new BalloonManager;
	GM->SetBalloonManager(balloonManager);

	streamManager = new StreamManager;
	GM->SetStreamManager(streamManager);

	itemManager = new ItemManager;

	dartManager = new DartManager;
	GM->SetDartManager(dartManager);
	
	uiManager = new GameUIManager;

	uiManager->SetLogoFinEvent(bind(&GameScene::StartGameFromSpawn, this));

	//SOUND->Play("VillageBGM", 1.f);
}

GameScene::~GameScene()
{
	delete tileManager;

	delete blockManager;

	delete playerManager;

	delete balloonManager;

	delete streamManager;

	delete itemManager;

	delete dartManager;

	delete uiManager;
}

void GameScene::Update()
{
	GM->Update();

	uiManager->Update();

	if (GM->IsEditMode())
	{
		MapEditor::GetInst()->Update();
		return;
	}


	playerManager->Update();

	dartManager->Update();
	tileManager->Update();
	blockManager->Update();
	balloonManager->Update();

	streamManager->Update();

	itemManager->Update();
	
	UpdateTimer();
}

void GameScene::Render()
{

	uiManager->Render();

	if (GM->IsEditMode())
	{
		MapEditor::GetInst()->Render();
		return;
	}

	tileManager->Render();
	blockManager->Render();
	balloonManager->Render();

	playerManager->Render();

	streamManager->Render();
	itemManager->Render();

	dartManager->Render();

	uiManager->RenderTimer(gameTimer);
	//p1->Debug();
	//p2->Debug();
}


void GameScene::StartGameFromSpawn()
{
	gameStatus = PLAY;

	for (Character* player : playerManager->GetWholePlayers())
		player->SetCharacterState(C_IDLE);
}

void GameScene::UpdateTimer()
{
	if (gameStatus != PLAY) return;

	if (gameStatus == GAME_OVER) return;

	gameTimer -= Time::Delta();

	// TODO : 타이머 출력

	if (gameTimer <= 0.f)
	{
		gameTimer = 0.f;
		gameStatus = GAME_OVER;
	}
}




	