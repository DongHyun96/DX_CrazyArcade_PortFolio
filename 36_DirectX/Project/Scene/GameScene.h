#pragma once


/* CONCRETE CLASS */
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	virtual void Update() override;
	virtual void Render() override;

public:

	void SetGameEnd(const GameOverResult& result);

private:

	void StartGameFromSpawn();
	void UpdateTimer();

	void CheckTimerAfterGameOver(); // 로비로 복귀하는 시간 체크
	void ExitToLobby();


private:

	// 나머지는 Archieve에 저장해놓고 돌아가면서 사용(게임이 끝난 뒤 LobbyScene에 돌아갈 때 초기화해 둠)

	TileManager*	tileManager{};  // 얘네만 다를 예정
	BlockManager*	blockManager{};

	GameUIManager*	uiManager{};

	PlayerManager*	playerManager{};

	BalloonManager*	balloonManager{}; 
	StreamManager*	streamManager{};

	ItemManager*	itemManager{};

	DartManager*	dartManager{};

private:
	/* 로비로 나가는 버튼 */
	Button*	exitToLobbyButton{};

private:

	const float GAME_TIME_TOTAL = 180.f;			// 게임플레이 시간제한
	float		gamePlayTimer	= GAME_TIME_TOTAL;	// 게임플레이 타이머

private: /* 게임 오버 후 적정 시간이 지나면 로비로 돌아감 */

	const float AFTER_GAMEOVER_TIME = 4.f; // 게임오버가 된 후 4초 뒤 로비로 복귀
	float		afterGameOverTime = 0.f;
};

