#include "Framework.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
	if (GM->IsEditMode())
	{
		mapEditor = new MapEditor;
	}
	else
	{
		scenes =
		{
			{INTRO_SCENE, new IntroScene},
			{LOBBY_SCENE, new LobbyScene},
			//{GAME_SCENE, new GameScene}
			{GAME_SCENE, nullptr}
		};
	}

	ShowCursor(false);

	mouse = new Object(L"InGame/Mouse/Mouse.png");
	mouseClicked = new Object(L"InGame/Mouse/MouseClicked.png");

	mouse->zDepth = -9.f;
	mouseClicked->zDepth = -9.f;
	mouse->scale = { 1.5f, 1.5f };
	mouseClicked->scale = { 1.5f, 1.5f };
	curMouse = mouse;

	gameExitPanel = new Object(L"InGame/UI/Panel.png");
	gameExitPanel->translation = {WIN_CENTER.x, WIN_HEIGHT + 300.f};
	gameExitPanel->zDepth = NEAR_Z + 3;
	gameExitPanel->scale = { 2.f, 2.f };

	gameExitButton = new Button(L"InGame/UI/exitButton.png", 2, 1, 2);
	gameExitButton->SetEvent(bind(&SceneManager::OnGameExit, this));
	gameExitButton->GetBody()->translation = {0.f, -20.f};
	gameExitButton->GetBody()->scale = { 1.f, 1.5f };
	gameExitButton->GetBody()->SetParent(gameExitPanel);
}

SceneManager::~SceneManager()
{
	for (auto& p : scenes)
	{
		if (p.second) delete p.second;
	}

	if (mapEditor) delete mapEditor;

	scenes.clear();

	delete mouse;
	delete mouseClicked;

	delete gameExitPanel;

	delete gameExitButton;
}

void SceneManager::Update()
{
	if (GM->IsEditMode())
		mapEditor->Update();
	else
		scenes[curScene]->Update();

	mouse->Update();
	mouseClicked->Update();

	gameExitPanel->Update();
	gameExitButton->Update();
	HandleGameExitPanel();

	if (KEY_PRESS(VK_LBUTTON) || KEY_PRESS(VK_RBUTTON))
		curMouse = mouseClicked;
	else
		curMouse = mouse;

	curMouse->translation = { mousePos.x + 20.f, mousePos.y - 25.f };
}

void SceneManager::Render()
{
	if (GM->IsEditMode())
		mapEditor->Render();
	else
		scenes[curScene]->Render();


	gameExitPanel->Render();
	gameExitButton->Render();

	curMouse->Render();

}

void SceneManager::SetCurScene(const SceneName& sceneName)
{
	if (sceneName == LOBBY_SCENE)
	{
		SOUND->Play("LobbyBGM", 1.f);

		if (curScene == GAME_SCENE)
		{
			// 게임씬에서 로비로 돌아올 때
			delete scenes[GAME_SCENE];
			scenes[GAME_SCENE] = nullptr;

		}
	}
	
	if (sceneName == GAME_SCENE)
	{

		for (UINT i = 0; i < 2; i++)
		{
			if (GM->P_SelectedCharacterMap()[(PlayerType)i] == RANDOM) 
				GM->P_SelectedCharacterMap()[(PlayerType)i] = (CharacterType)(Util::GetRandom(0, 3));
				
		}

		GM->InitGame();

		if (scenes[GAME_SCENE])
		{
			delete scenes[GAME_SCENE];
			scenes[GAME_SCENE] = nullptr;
		}

		scenes[GAME_SCENE] = new GameScene; // Load gameData (블록과 타일정보 로드

		// 한번 타임을 elapsed를 초기화 시켜줘야 함
		Time::GetInstance()->RefreshTimer();

		SOUND->Stop("LobbyBGM");

	}

	curScene = sceneName;
}

void SceneManager::HandleGameExitPanel()
{
	static bool isLerping{false};
	static const float EXIT_PANEL_ORIGIN = WIN_HEIGHT + 300.f;
	static map<bool, float> destMap{ {false, EXIT_PANEL_ORIGIN}, {true, WIN_CENTER.y} };
	static bool destFlag = true;


	if (KEY_DOWN(VK_ESCAPE)) isLerping = true;

	if (!isLerping) return;

	gameExitPanel->translation.y = Util::Lerp(gameExitPanel->translation.y, destMap[destFlag], Time::Delta() * 15.f);

	if (abs(gameExitPanel->translation.y - destMap[destFlag]) < 1.f) // Lerp fin
	{
		destFlag = !destFlag;
		isLerping = false;
	}
}
