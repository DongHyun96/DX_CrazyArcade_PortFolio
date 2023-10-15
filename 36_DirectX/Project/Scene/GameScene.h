#pragma once

enum GameStatus
{
	START,
	PLAY,
	GAME_OVER
};

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	virtual void Update() override;
	virtual void Render() override;

private:

	void StartGameFromSpawn();
	void UpdateTimer();


private:

	GameUIManager* uiManager{};

	PlayerManager* playerManager{};

	TileManager* tileManager{};
	BlockManager* blockManager{};

	BalloonManager* balloonManager{}; // TODO ������ �� �ݹ����� �÷��̾��� balloonCnt���� 1�� ������� ��
	StreamManager* streamManager{};

	ItemManager* itemManager{};

	DartManager* dartManager{};

private:

	GameStatus gameStatus{ START };

	const float GAME_TIME_LIMIT = 180.f;
	float gameTimer = GAME_TIME_LIMIT;

};

