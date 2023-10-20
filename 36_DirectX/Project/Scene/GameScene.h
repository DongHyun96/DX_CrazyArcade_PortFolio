#pragma once



class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	virtual void Update() override;
	virtual void Render() override;

	void SetGameEnd(const GameOverResult& result); // PM과 자기자신에서 Call(시간초과 draw)



private:

	void StartGameFromSpawn();
	void UpdateTimer();

	void CheckTimerAfterGameOver(); // 로비로 복귀하는 시간 체크
	void ExitToLobby();


private:

	// 나머지는 Archieve에 저장해놓고 돌아가면서 사용(게임이 끝난 뒤 LobbyScene에 돌아갈 때 초기화해 둠)

	GameUIManager*		uiManager{};

	PlayerManager*		playerManager{};
	
	TileManager*		tileManager{};  // 얘네만 다를 예정
	BlockManager*		blockManager{};

	BalloonManager*		balloonManager{}; 
	StreamManager*		streamManager{};

	ItemManager*		itemManager{};

	DartManager*		dartManager{};

	Button*				exitButton{};

private:

	const float GAME_TIME_TOTAL = 180.f;
	float gameTimer = GAME_TIME_TOTAL;

private:

	bool renderedOnce{};

private:

	const float AFTER_GAMEOVER_TIME = 4.f; // 게임오버가 된 후 4초 뒤 로비로 복귀
	float afterGameOverTime = 0.f;
};

