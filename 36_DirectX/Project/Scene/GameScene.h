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

	void CheckTimerAfterGameOver(); // �κ�� �����ϴ� �ð� üũ
	void ExitToLobby();


private:

	// �������� Archieve�� �����س��� ���ư��鼭 ���(������ ���� �� LobbyScene�� ���ư� �� �ʱ�ȭ�� ��)

	TileManager*	tileManager{};  // ��׸� �ٸ� ����
	BlockManager*	blockManager{};

	GameUIManager*	uiManager{};

	PlayerManager*	playerManager{};

	BalloonManager*	balloonManager{}; 
	StreamManager*	streamManager{};

	ItemManager*	itemManager{};

	DartManager*	dartManager{};

private:
	/* �κ�� ������ ��ư */
	Button*	exitToLobbyButton{};

private:

	const float GAME_TIME_TOTAL = 180.f;			// �����÷��� �ð�����
	float		gamePlayTimer	= GAME_TIME_TOTAL;	// �����÷��� Ÿ�̸�

private: /* ���� ���� �� ���� �ð��� ������ �κ�� ���ư� */

	const float AFTER_GAMEOVER_TIME = 4.f; // ���ӿ����� �� �� 4�� �� �κ�� ����
	float		afterGameOverTime = 0.f;
};

