#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	GM->SetGameScene(this);

	tileManager = new TileManager;

	blockManager = new BlockManager;
	GM->SetBlockManager(blockManager);

	playerManager = new PlayerManager;
	GM->SetPlayerManager(playerManager);

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

void GameScene::SetGameEnd(const GameOverResult& result)
{
	GM->SetGameStatus(GAME_OVER);

	uiManager->StartRenderGameOver(result);

	playerManager->SetGameOver();

	//P1_WIN,
	//P2_WIN,
	//ENEMY_WIN,
	//DRAW
	if (result == P1_WIN || result == P2_WIN)
		SOUND->Play("Win", 1.f);
	else if (result == ENEMY_WIN)
		SOUND->Play("Lose", 1.f);
	else
		SOUND->Play("Draw", 1.f);

	SOUND->Pause("VillageBGM");
}


void GameScene::StartGameFromSpawn()
{
	GM->SetGameStatus(PLAY);

	for (Character* player : playerManager->GetWholePlayers())
		player->SetCharacterState(C_IDLE);
}

void GameScene::UpdateTimer()
{
	if (GM->GetGameStatus() != PLAY) return;

	if (GM->GetGameStatus() == GAME_OVER) return;

	gameTimer -= Time::Delta();

	if (gameTimer <= 0.f)
	{
		gameTimer = 0.f;
		SetGameEnd(DRAW);
	}
}

