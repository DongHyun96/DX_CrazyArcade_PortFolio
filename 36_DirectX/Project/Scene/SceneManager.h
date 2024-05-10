#pragma once

enum SceneName
{
	INTRO_SCENE,
	LOBBY_SCENE,
	GAME_SCENE
};

/*
CONCRETE CLASS | SINGLETON
��ü scene �� scene ��ȯ ��� manager
*/
class SceneManager : public Singleton<SceneManager>
{

	friend class Singleton;

private:
	SceneManager();
	~SceneManager();

public:
	
	void Update();
	void Render();

private:

	void		SetCurScene(const SceneName& sceneName);
	SceneName	GetCurSceneName() const { return curScene; }

private:

	void HandleGameExitPanel();
	
	void OnGameExit() { PostQuitMessage(0); }

private:
	
	map<SceneName, Scene*>	scenes{};					// ��� scene
	SceneName				curScene{ INTRO_SCENE };	// ���� scene
	
private:

	MapEditor* mapEditor{};

private: /* ���콺 ������ texture ���� */

	Object* idleMouseTexture{};		
	Object* mouseClickedTexture{};

	Object* curMouseTexture{}; 
	bool	isCustomCursor = true;

private: /* ���� �����ư �г� ���� */

	Object* gameExitPanel{};
	Button* gameExitButton{};

};
