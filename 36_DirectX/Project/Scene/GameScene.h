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

	/* GameOverResult�� ���� GameScene�������� GameOveró�� */
	void SetGameEnd(const GameOverResult& result);

private:

	/* Game start logo animation�� ���� ��, �÷��̾� SPAWN���� ������ ���������� play�����ϰ� game start*/
	void StartGameFromSpawn();

private:
	/* ���� Ÿ�̸� ������Ʈ */
	void UpdateTimer();

private:

	/* �κ�� �����ϴ� �ð� üũ */
	void CheckTimerAfterGameOver();

	void ExitToLobby();


private: /* GameScene���� ��ȯ(GameScene ����) �� ���� ���Ӹʿ� �ش��ϴ� ���ο� tileManager�� blockManager ���� */

	TileManager*	tileManager{};
	BlockManager*	blockManager{};

private: /* GameManager�� �̸� �����ص� manager�� */

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

