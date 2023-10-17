#pragma once

enum SceneName
{
	INTRO_SCENE,
	LOBBY_SCENE,
	GAME_SCENE
};

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

public:
	static SceneManager* GetInst()
	{
		static SceneManager singleton;
		return &singleton;
	}
	
	void Update();
	void Render();

	void SetCurScene(const SceneName& sceneName)
	{
		if (sceneName == GAME_SCENE)
		{
			SOUND->Play("GameStart", 0.5f);
			SOUND->Play("VillageBGM", 1.f);
		}
		curScene = sceneName; 
	}

private:

	void LoadingThread();

private:
	
	map<SceneName, Scene*> scenes{};

	SceneName curScene{ INTRO_SCENE };
	
	MapEditor* mapEditor{};

private:

	mutex loadingMutex{};
	bool isLoadingComplete = false;

};
