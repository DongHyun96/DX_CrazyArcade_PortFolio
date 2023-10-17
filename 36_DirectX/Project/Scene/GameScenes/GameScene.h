#pragma once



class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual void Update() override;
	virtual void Render() override;

	void SetGameEnd(const GameOverResult& result);


private:

	void StartGameFromSpawn();
	void UpdateTimer();


private:

	// �������� Archieve�� �����س��� ���ư��鼭 ���(������ ���� �� LobbyScene�� ���ư� �� �ʱ�ȭ�� ��)

	GameUIManager*		uiManager{};

	PlayerManager*		playerManager{};
	
	TileManager*		tileManager{};  // ��׸� �ٸ� ����
	BlockManager*		blockManager{};

	BalloonManager*		balloonManager{}; 
	StreamManager*		streamManager{};

	ItemManager*		itemManager{};

	DartManager*		dartManager{};

private:

	const float GAME_TIME_TOTAL = 180.f;
	float gameTimer = GAME_TIME_TOTAL;

private:
	bool renderedOnce{};
};

