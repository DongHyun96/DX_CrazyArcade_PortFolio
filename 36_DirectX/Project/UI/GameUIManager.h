#pragma once

/* GameOver 결과 */
enum GameOverResult
{
	P1_WIN,
	P2_WIN,
	ENEMY_WIN,
	DRAW
};

/*
CONCRETE CLASS
GameScene UI 담당
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
	/// <para> Start Logo가 위로 모두 올라가면 trigger될 function pointer setter </para>
	/// <para> 실질적인 인게임 시작점 함수를 setting한다고 볼 수 있음 </para>
	/// </summary>
	/// <param name="LogoEndEvent"> : Call-back funcion pointer </param>
	void SetStartLogoFinEvent(function<void()> LogoEndEvent); // Whole GameStart Trigger

	/// <summary>
	/// 게임 타이머(우측 상단) 출력
	/// </summary>
	/// <param name="gameTimer"> : Game play timer time </param>
	void RenderTimer(const float& gameTimer);
	
	/// <summary>
	/// GameOverResult에 따라 GameOver UI 처리
	/// </summary>
	/// <param name="result"> GameOver 결과 </param>
	void StartRenderGameOver(const GameOverResult& result);

private: 

	void RenderStartLogo();
	void UpdateStartLogo();

	void RenderGameOver();
	void UpdateGameOver();

private:

	void Debug();

private:

	Object* mainUI{}; // 기본 전체 main panel texture object
	Object* itemUI{}; // 아이템 창 texture object

private: /* Game start 관련 */

	bool			hasGameStarted{};
	vector<Object*> startLogo{};					// Start logo alphbet textures

	const float		START_LOGO_TIME_TICK = 0.15f;
	const float		START_LOGO_SPEED	 = 2000.f;
	float			startLogoTime{};

	function<void()> StartLogoFinEvent{};			// Start logo 애니메이션이 끝난 후 호출될 함수 포인터

private: /* GameOver 관련 */

	bool							gameOver{};

	map<GameOverResult, Object*>	gameOverPanel{};
	
	GameOverResult					gameOverResult{};

	/* GameOver 로고 flicker 관련 */

	const Vector4					FLICKER_COLOR{ 0, 0, 0, 1 };
	float							flicker{};
	bool							flicked{};
	UINT							flickedCnt{};

};
