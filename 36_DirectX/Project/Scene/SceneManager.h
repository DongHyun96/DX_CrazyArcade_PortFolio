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

	void SetCurScene(const SceneName& sceneName)
	{
		if (sceneName == GAME_SCENE)
		{
			scenes[GAME_SCENE] = new GameScene; // Load gameData

			GM->GetPlayerManager()->Init();

			// �ѹ� Ÿ���� elapsed�� �ʱ�ȭ ������� ��
			Time::GetInstance()->RefreshTimer();
		}


		curScene = sceneName; 
	}

	SceneName GetCurSceneName() const { return curScene; }

private:
	
	map<SceneName, Scene*> scenes{};

	SceneName curScene{ INTRO_SCENE };
	
	MapEditor* mapEditor{};

private:


};
