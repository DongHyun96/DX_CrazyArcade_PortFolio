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
			{LOBBY_SCENE, nullptr},
			//{GAME_SCENE, new GameScene}
			{GAME_SCENE, nullptr}
		};
	}
}

SceneManager::~SceneManager()
{
	for (auto& p : scenes)
	{
		if (p.second) delete p.second;
	}

	if (mapEditor) delete mapEditor;

	scenes.clear();
}

void SceneManager::Update()
{
	if (GM->IsEditMode())
		mapEditor->Update();
	else
		scenes[curScene]->Update();
}

void SceneManager::Render()
{
	if (GM->IsEditMode())
		mapEditor->Render();
	else
		scenes[curScene]->Render();
}

void SceneManager::SetCurScene(const SceneName& sceneName)
{
	if (sceneName == GAME_SCENE)
	{
		GM->InitGame();

		if (scenes[GAME_SCENE])
			delete scenes[GAME_SCENE];

		scenes[GAME_SCENE] = new GameScene; // Load gameData (블록과 타일정보 로드

		// 한번 타임을 elapsed를 초기화 시켜줘야 함
		Time::GetInstance()->RefreshTimer();
	}

	curScene = sceneName;
}
