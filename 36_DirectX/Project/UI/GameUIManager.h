#pragma once
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

private:

	void RenderStartLogo();


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



};
