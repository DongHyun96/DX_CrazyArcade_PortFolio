#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	GM->SetGameScene(this);

	tileManager = new TileManager;

	blockManager = new BlockManager;
	GM->SetBlockManager(blockManager);

	playerManager = GM->GetPlayerManager();

	balloonManager = GM->GetBalloonManager();

	streamManager = GM->GetStreamManager();

	itemManager = GM->GetItemManager();

	dartManager = GM->GetDartManager();
	
	uiManager = GM->GetGameUIManager();

	uiManager->SetLogoFinEvent(bind(&GameScene::StartGameFromSpawn, this)); // 이게 게임 start 트리거

	float volume =  GM->GetCurMapType() == VILLAGE ? 1.f :
					GM->GetCurMapType() == FOREST ? 0.7f : 0.7f;

	SOUND->Play(GM->mapBGM[GM->GetCurMapType()], volume);

}

GameScene::~GameScene()
{
	delete tileManager;

	delete blockManager;
}

void GameScene::Update()
{
	if (KEY_DOWN(VK_F3))
	{
		SM->SetCurScene(INTRO_SCENE);
		SOUND->Stop(GM->mapBGM[GM->GetCurMapType()]);
		return;
	}

	uiManager->Update();

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

	SOUND->Pause(GM->mapBGM[GM->GetCurMapType()]);
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

	gameTimer -= Time::Delta();

	if (gameTimer <= 0.f)
	{
		gameTimer = 0.f;
		SetGameEnd(DRAW);
	}
}

