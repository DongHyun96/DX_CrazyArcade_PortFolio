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

}

GameUIManager::~GameUIManager()
{
	delete mainUI;
	delete itemUI;

	for (Object* letter : startLogo)
		delete letter;
}

void GameUIManager::Update()
{
	mainUI->Update();
	itemUI->Update();

	RenderStartLogo();
}


void GameUIManager::Render()
{
	mainUI->Render();
	itemUI->Render();

	for (Object* letter : startLogo)
		letter->Render();

	Debug();
}

void GameUIManager::RenderStartLogo()
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


void GameUIManager::RenderTimer(const float& gameTimer)
{
	UINT minute = gameTimer / 60;
	UINT second = gameTimer - minute * 60;

	//if (second < 10)

	wstring watch = (second >= 10) ? L"0" + to_wstring(minute) + L":" + to_wstring(second)
		: L"0" + to_wstring(minute) + L":0" + to_wstring(second);

	FONT->RenderText(watch, "NumberFont", Util::ConvertDxPosToAPIPos({ 1723, 1000 }));
}

void GameUIManager::SetLogoFinEvent(function<void()> LogoEndEvent)
{
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

	ImGui::BeginGroup();

	ImGui::Begin("MousePos");
	ImGui::InputFloat2("XY", (float*)&mousePos);
	Vector2 size = itemUI->GetSize();
	ImGui::InputFloat2("XY", (float*)&size);
	Vector2 temp = startLogo[3]->GlobalPosition();
	ImGui::InputFloat2("LogoXY", (float*)&temp);
	ImGui::End();

	ImGui::EndGroup();

}

void GameUIManager::Init()
{
}
