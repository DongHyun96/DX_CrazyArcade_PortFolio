#pragma once

class CharacterAnim;

#define SPEED_BASE 70.f

enum CharacterType
{
	BAZZI,
	DAO,
	CAPPI,
	MARID
};

enum CharacterState
{
	C_SPAWN,

	C_IDLE,

	C_SPACECRAFT,
	C_OWL,
	C_TURTLE,

	C_CAPTURED,

	C_RETURN_IDLE,

	C_DEAD
};

static struct SpeedLv
{
	static const UINT capturedSpeedLv	= 1;
	static const UINT spaceSpeedLv		= 10;
	static const UINT owlSpeedLv		= 6;
	static const UINT turtleSpeedLv		= 2;
};

class Character : public ColliderHolder
{
public:
	Character(const CharacterType& cType);

	virtual ~Character();

	virtual void Update();
	virtual void Render();

	virtual void Move() = 0;

public:
	void Debug();

	void SetLabel(const string& label) { this->label = label; }

public:

	void SetCharacterState(const CharacterState& state);

	CharacterState GetCharacterState() const { return mainState; }

	void SetVisible(const bool& visible) { this->visible = visible; }

	ColliderRect* GetBody() const { return body; }

	ColliderRect* GetPushCollider() const { return pushCollider; }

	Vector2 GetVelocity() const { return velocity; }

	UINT GetStreamLv() const { return streamLv; }

	bool AddLeftBalloonCnt(const UINT& addAmount = 1); // Balloon 회수 또는 Item Usage에 사용

public: // Item Usage

	bool IncreaseSpeed(bool increaseToMax = false);
	bool IncreaseStreamLv(bool increaseToMax = false);

private:

	void HandleBoundary();

	virtual void DeployBalloon() = 0;

protected:

	ColorBuffer* colorBuffer{};
	bool visible{ true };

	void InitStat(const CharacterType& cType);

	void OnEndReturnToIdle()	{ SetCharacterState(C_IDLE); }
	void OnCapturedEnd()		{ SetCharacterState(C_DEAD); }

protected:

	ColliderRect*	body{};
	Vector2			velocity{};

	CharacterState	mainState{C_IDLE};

	CharacterAnim*	actionHandler; // 실질적인 캐릭터 출력물 담당

	string			label{};
	
protected:

	ColliderRect* pushCollider{}; // 밀어낼 수 있는 블록용도로 쓸 것임


protected:

	/*
	속도 / 물풍선 / 물줄기
	*/
	UINT speedLvMin{};
	UINT speedLvMax{};

	UINT curIdleSpeedLv{}; // Idle 상태일 때의 speed를 저장하기 위한 변수
	UINT speedLv{}; // 현재(탈 것 포함)의 speed

	UINT balloonCntMin{};
	UINT balloonCntMax{};
	UINT leftBalloonCnt{};

	UINT streamLvMin{};
	UINT streamLvMax{};
	UINT streamLv{}; // CurrentStreamLv


};

