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

