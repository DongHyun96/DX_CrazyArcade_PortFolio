#pragma once

enum SceneName
{
	INTRO_SCENE,
	LOBBY_SCENE,
	GAME_SCENE
};

/*
CONCRETE CLASS | SINGLETON
전체 scene 및 scene 전환 담당 manager
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

public:

	void		SetCurScene(const SceneName& sceneName);
	SceneName	GetCurSceneName() const { return curScene; }

private:

	void HandleGameExitPanel();
	
	void OnGameExit() { PostQuitMessage(0); }

private:
	
	map<SceneName, Scene*>	scenes{};					// 모든 scene
	SceneName				curScene{ INTRO_SCENE };	// 현재 scene
	
private:

	MapEditor* mapEditor{};

private: /* 마우스 포인터 texture 관련 */

	Object* idleMouseTexture{};		
	Object* mouseClickedTexture{};

	Object* curMouseTexture{}; 
	bool	isCustomCursor = true;

private: /* 게임 종료버튼 패널 관련 */

	Object* gameExitPanel{};
	Button* gameExitButton{};

};
