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

	void SetCurScene(const SceneName& sceneName) { curScene = sceneName; }

private:
	
	map<SceneName, Scene*> scenes{};

	SceneName curScene{ INTRO_SCENE };

};
