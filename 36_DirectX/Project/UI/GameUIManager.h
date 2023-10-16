#pragma once

enum GameOverResult
{
	P1_WIN,
	P2_WIN,
	ENEMY_WIN,
	DRAW
};


class GameUIManager : public UIManager
{
public:
	GameUIManager();
	~GameUIManager();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Init() override;


public:

	void SetLogoFinEvent(function<void()> LogoEndEvent);
	void RenderTimer(const float& gameTimer);
	
	void StartRenderGameOver(const GameOverResult& result);

private:

	void RenderStartLogo();
	void UpdateStartLogo();

	void RenderGameOver();
	void UpdateGameOver();

	void Debug();

private:

	Object* mainUI{};
	Object* itemUI{};


private:

	bool hasGameStarted{};
	vector<Object*> startLogo{};

	const float LOGO_TIME_TICK = 0.15f;
	const float LOGO_SPEED = 2500.f;
	float logoTime = 0.f;

	function<void()> LogoFinEvent{};

private:

	map<GameOverResult, Object*> gameOverPanel{};
	
	bool gameOver{ };
	GameOverResult gameOverResult{};

	const Vector4 FLICKER_COLOR{ 0, 0, 0, 1 };
	float flicker{};
	bool flicked{};
	UINT flickedCnt{};

};
