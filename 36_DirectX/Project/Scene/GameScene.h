#pragma once


/*
CONCRETE CLASS
In-game scene class
*/
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	virtual void Update() override;
	virtual void Render() override;

public:

	/* GameOverResult에 따른 GameScene내에서의 GameOver처리 */
	void SetGameEnd(const GameOverResult& result);

private:

	/* Game start logo animation이 끝난 뒤, 플레이어 SPAWN상태 끝내고 실질적으로 play가능하게 game start*/
	void StartGameFromSpawn();

private:
	/* 게임 타이머 업데이트 */
	void UpdateTimer();

private:

	/* 로비로 복귀하는 시간 체크 */
	void CheckTimerAfterGameOver();

	void ExitToLobby();


private: /* GameScene으로 전환(GameScene 생성) 시 현재 게임맵에 해당하는 새로운 tileManager와 blockManager 생성 */

	TileManager*	tileManager{};
	BlockManager*	blockManager{};

private: /* GameManager에 미리 저장해둔 manager들 */

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

