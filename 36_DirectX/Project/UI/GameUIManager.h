#pragma once

/* GameOver ��� */
enum GameOverResult
{
	P1_WIN,
	P2_WIN,
	ENEMY_WIN,
	DRAW
};

/*
CONCRETE CLASS
GameScene UI ���
*/
class GameUIManager : public UIManager
{
public:
	GameUIManager();
	~GameUIManager();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Init() override;


public:

	/// <summary>
	/// <para> Start Logo�� ���� ��� �ö󰡸� trigger�� function pointer setter </para>
	/// <para> �������� �ΰ��� ������ �Լ��� setting�Ѵٰ� �� �� ���� </para>
	/// </summary>
	/// <param name="LogoEndEvent"> : Call-back funcion pointer </param>
	void SetStartLogoFinEvent(function<void()> LogoEndEvent); // Whole GameStart Trigger

	/// <summary>
	/// ���� Ÿ�̸�(���� ���) ���
	/// </summary>
	/// <param name="gameTimer"> : Game play timer time </param>
	void RenderTimer(const float& gameTimer);
	
	/// <summary>
	/// GameOverResult�� ���� GameOver UI ó��
	/// </summary>
	/// <param name="result"> GameOver ��� </param>
	void StartRenderGameOver(const GameOverResult& result);

private: 

	void RenderStartLogo();
	void UpdateStartLogo();

	void RenderGameOver();
	void UpdateGameOver();

private:

	void Debug();

private:

	Object* mainUI{}; // �⺻ ��ü main panel texture object
	Object* itemUI{}; // ������ â texture object

private: /* Game start ���� */

	bool			hasGameStarted{};
	vector<Object*> startLogo{};					// Start logo alphbet textures

	const float		START_LOGO_TIME_TICK = 0.15f;
	const float		START_LOGO_SPEED	 = 2000.f;
	float			startLogoTime{};

	function<void()> StartLogoFinEvent{};			// Start logo �ִϸ��̼��� ���� �� ȣ��� �Լ� ������

private: /* GameOver ���� */

	bool							gameOver{};

	map<GameOverResult, Object*>	gameOverPanel{};
	
	GameOverResult					gameOverResult{};

	/* GameOver �ΰ� flicker ���� */

	const Vector4					FLICKER_COLOR{ 0, 0, 0, 1 };
	float							flicker{};
	bool							flicked{};
	UINT							flickedCnt{};

};
