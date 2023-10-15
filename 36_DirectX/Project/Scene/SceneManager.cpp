#include "Framework.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
	scenes =
	{
		{INTRO_SCENE, new IntroScene},
		{LOBBY_SCENE, nullptr},
		{GAME_SCENE, new GameScene}
	};
}

SceneManager::~SceneManager()
{
	for (auto& p : scenes)
	{
		if (p.second) delete p.second;
	}

	scenes.clear();
}

void SceneManager::Update()
{


	scenes[curScene]->Update();
}

void SceneManager::Render()
{
	scenes[curScene]->Render();
}
