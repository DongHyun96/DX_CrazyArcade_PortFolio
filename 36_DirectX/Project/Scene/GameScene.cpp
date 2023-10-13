#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	tileManager = new TileManager;

	blockManager = new BlockManager;
	GM->SetBlockManager(blockManager);

	p1 = new Player(BAZZI, P1);
	p1->SetLabel("P1");

	p2 = new Player(BAZZI, P2);
	p2->SetLabel("P2");

	GM->SetPlayers(p1, p2);
	
	vector<Util::Coord> spawnPos = GM->spawnPosMap[GM->GetCurMapType()];

	random_shuffle(spawnPos.begin(), spawnPos.end());

	p1->SetSpawnPos(spawnPos[0]);
	p2->SetSpawnPos(spawnPos[1]);

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
	delete tileManager;
	delete blockManager;

	delete p1;
	delete p2;

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

	p1->Update();
	p2->Update();

	dartManager->Update();
	tileManager->Update();
	blockManager->Update();
	balloonManager->Update();

	streamManager->Update();

	itemManager->Update();

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

	p1->Render();
	p2->Render();

	streamManager->Render();
	itemManager->Render();

	dartManager->Render();

	//p1->Debug();
	//p2->Debug();
}




	