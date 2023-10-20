#pragma once

enum SceneName
{
	INTRO_SCENE,
	LOBBY_SCENE,
	GAME_SCENE
};

class SceneManager : public Singleton<SceneManager>
{

	friend class Singleton;

private:
	SceneManager();
	~SceneManager();

public:
	
	void Update();
	void Render();

	void SetCurScene(const SceneName& sceneName);

	SceneName GetCurSceneName() const { return curScene; }

private:

	void HandleGameExitPanel();
	
	void OnGameExit() { PostQuitMessage(0); }

private:
	
	map<SceneName, Scene*> scenes{};

	SceneName curScene{ INTRO_SCENE };
	
	MapEditor* mapEditor{};

private:

	Object* mouse{};
	Object* mouseClicked{};

	Object* curMouse{};

	Object* gameExitPanel{};
	Button* gameExitButton{};
	

};
