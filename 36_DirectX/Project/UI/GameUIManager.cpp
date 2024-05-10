#include "Framework.h"
#include "GameUIManager.h"


GameUIManager::GameUIManager()
{
	mainUI = new Object(WIN_SIZE, L"InGame/UI/mapToolMap.png");
	//mainUI = new Object(WIN_SIZE, L"InGame/UI/map.png");

	mainUI->translation = WIN_CENTER;
	mainUI->zDepth = FAR_Z - 1;

	itemUI = new Object(L"Ingame/UI/ItemUI.png");
	itemUI->translation = { 1727, 175 };
	itemUI->scale = { 2.0f, 1.2f };
	itemUI->zDepth = FAR_Z - 2;

	for (UINT i = 0; i < 6; i++)
	{
		Object* letter = new Object(L"InGame/UI/StartLogo/" + to_wstring(i) + L".png");
		letter->translation.x = (WIN_CENTER.x - 500.f) + i * 200 - WIN_CENTER.x;
		letter->scale = { 2.f, 2.f };
		letter->zDepth = -5.f;
		letter->SetParent(GM->GetGameFieldTransform());

		startLogo.push_back(letter);
	}

	//{600, 300},
	//{ 600, 300 },

	gameOverPanel =
	{
		{P1_WIN,	new Object(L"InGame/UI/player1win.png")},
		{P2_WIN,	new Object(L"InGame/UI/player2win.png")},
		{ENEMY_WIN, new Object(L"InGame/UI/Lose.png")},
		{DRAW,		new Object(L"InGame/UI/draw.png")}
	};

	for (auto& p : gameOverPanel)
		p.second->zDepth = -5.f;


	gameOverPanel[P1_WIN]->scale	= {2.f, 2.f};
	gameOverPanel[P2_WIN]->scale	= {2.f, 2.f};
	gameOverPanel[DRAW]->scale		= {2.f, 2.f};
	gameOverPanel[ENEMY_WIN]->scale = {2.6f, 3.f};


	
	for (auto& p : gameOverPanel)
	{
		Object* o = p.second;

		o->SetParent(GM->GetGameFieldTransform());
	}

}

GameUIManager::~GameUIManager()
{
	delete mainUI;
	delete itemUI;

	for (Object* letter : startLogo)
		delete letter;

	for (auto& p : gameOverPanel)
		delete p.second;

}

void GameUIManager::Update()
{
	mainUI->Update();
	itemUI->Update();

	UpdateStartLogo();

	UpdateGameOver();
}


void GameUIManager::Render()
{
	mainUI->Render();
	itemUI->Render();

	RenderStartLogo();
	RenderGameOver();

	Debug();
}

void GameUIManager::RenderStartLogo()
{
	for (Object* letter : startLogo)
		letter->Render();
}

void GameUIManager::UpdateStartLogo()
{
	if (hasGameStarted)
	{
		logoTime += Time::Delta();

		for (UINT i = 0; i < 6; i++)
		{
			startLogo[i]->Update();

			if (logoTime >= LOGO_TIME_TICK * (i + 1))
				startLogo[i]->translation.y += LOGO_SPEED * Time::Delta();
		}

		if (startLogo.back()->GlobalPosition().y > WIN_HEIGHT + 200.f)
		{
			hasGameStarted = false;
			if (LogoFinEvent) LogoFinEvent();
		}

	}
}

void GameUIManager::RenderGameOver()
{
	if (!gameOver)
		return;

	// TODO -> GameOverResult gameOverResult{};에 맞추어 result 출력


	gameOverPanel[gameOverResult]->Render();

}

void GameUIManager::UpdateGameOver()
{
	if (!gameOver)
		return;

	flicker += Time::Delta();

	if (flicker >= 0.05f && flickedCnt < 8)
	{
		if (flicked) gameOverPanel[gameOverResult]->SetColor(1,1,1,1);
		else gameOverPanel[gameOverResult]->SetColor(FLICKER_COLOR);

		flicked = !flicked;
		flicker -= 0.05f;

		flickedCnt++;
	}

	// TODO -> GameOverResult gameOverResult{};에 맞추어 result 출력
	gameOverPanel[gameOverResult]->Update();
}


void GameUIManager::RenderTimer(const float& gameTimer)
{
	UINT minute = gameTimer / 60;
	UINT second = gameTimer - minute * 60;

	//if (second < 10)

	wstring watch = (second >= 10) ? L"0" + to_wstring(minute) + L":" + to_wstring(second)
		: L"0" + to_wstring(minute) + L":0" + to_wstring(second);

	FONT->RenderText(watch, "NumberFont", Util::ConvertDxPosToAPIPos({ 1723, 1000 }));
}

void GameUIManager::StartRenderGameOver(const GameOverResult& result)
{
	gameOver = true;
	this->gameOverResult = result;
}

void GameUIManager::SetStartLogoFinEvent(function<void()> LogoEndEvent)
{
	SOUND->Play("GameStart", 0.5f);

	this->LogoFinEvent = LogoEndEvent;

	hasGameStarted = true;

	for (Object* letter : startLogo)
		letter->translation.y = 0.f;

	logoTime = 0.f;

}

void GameUIManager::Debug()
{
	//if (ImGui::BeginMenu("GameUIManager"))
	//{
	//	ImGui::InputFloat2("MousePos", (float*)&mousePos);
	//	

	//	ImGui::EndMenu();
	//}

	// ImGui::InputFloat("Y", &itemUI->GetSize().y);

	//ImGui::BeginGroup();

	//ImGui::Begin("MousePos");
	//ImGui::InputFloat2("XY", (float*)&mousePos);
	//Vector2 size = itemUI->GetSize();
	//ImGui::InputFloat2("XY", (float*)&size);
	//Vector2 temp = startLogo[3]->GlobalPosition();
	//ImGui::InputFloat2("LogoXY", (float*)&temp);
	//ImGui::End();

	//ImGui::EndGroup();
}

void GameUIManager::Init()
{
	hasGameStarted = false;

	logoTime = 0.f;

	LogoFinEvent = nullptr;

	gameOver = false;

	flicker = 0.f;
	flicked = false;
	flickedCnt = 0;

	for (UINT i = 0; i < startLogo.size(); i++)
	{
		startLogo[i]->translation.y = 0;
		startLogo[i]->translation.x = (WIN_CENTER.x - 500.f) + i * 200 - WIN_CENTER.x;
	}

}
