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

	if (isCustomCursor) ShowCursor(false);
		

	idleMouseTexture = new Object(L"InGame/Mouse/Mouse.png");
	mouseClickedTexture = new Object(L"InGame/Mouse/MouseClicked.png");

	idleMouseTexture->zDepth = -9.f;
	mouseClickedTexture->zDepth = -9.f;
	idleMouseTexture->scale = { 1.5f, 1.5f };
	mouseClickedTexture->scale = { 1.5f, 1.5f };
	curMouseTexture = idleMouseTexture;

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

	delete idleMouseTexture;
	delete mouseClickedTexture;

	delete gameExitPanel;

	delete gameExitButton;
}

void SceneManager::Update()
{
	if (GM->IsEditMode())
		mapEditor->Update();
	else
		scenes[curScene]->Update();

	idleMouseTexture->Update();
	mouseClickedTexture->Update();

	gameExitPanel->Update();
	gameExitButton->Update();
	HandleGameExitPanel();

	if (KEY_PRESS(VK_LBUTTON) || KEY_PRESS(VK_RBUTTON))
		curMouseTexture = mouseClickedTexture;
	else
		curMouseTexture = idleMouseTexture;

	curMouseTexture->translation = { mousePos.x + 20.f, mousePos.y - 25.f };
}

void SceneManager::Render()
{
	if (GM->IsEditMode())
		mapEditor->Render();
	else
		scenes[curScene]->Render();


	gameExitPanel->Render();
	gameExitButton->Render();

	if (isCustomCursor) curMouseTexture->Render();
	

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

			LobbyScene* ls = dynamic_cast<LobbyScene*>(scenes[LOBBY_SCENE]);

			if (ls) ls->InitPlayerCharacters(); // 랜덤 선택되어 있었다면 플레이어를 다시 랜덤으로 바꿈

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

	if (GM->IsEditMode())
	{
		if (KEY_DOWN(VK_ESCAPE)) PostQuitMessage(0);

		return;
	}


	if (KEY_DOWN(VK_ESCAPE)) isLerping = true;

	if (!isLerping) return;

	gameExitPanel->translation.y = Util::Lerp(gameExitPanel->translation.y, destMap[destFlag], Time::Delta() * 15.f);

	if (abs(gameExitPanel->translation.y - destMap[destFlag]) < 1.f) // Lerp fin
	{
		destFlag = !destFlag;
		isLerping = false;
	}
}
