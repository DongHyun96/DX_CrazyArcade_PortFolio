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
	static const UINT owlSpeedLv		= 7;
	static const UINT turtleSpeedLv		= 3;
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

	void AddLeftBalloonCnt(const UINT& addAmount = 1);

public: // Item Usage

	void IncreaseSpeed(bool increaseToMax = false);


private:

	void HandleBoundary();

	virtual void DeployBalloon() = 0;

protected:

	ColorBuffer* colorBuffer{};
	bool visible{ true };

	void InitStat(const CharacterType& cType);

protected:

	ColliderRect*	body{};
	Vector2			velocity{};

	CharacterState	mainState{C_IDLE};

	CharacterAnim*	actionHandler;

	string			label{};
	
protected:

	ColliderRect* pushCollider{}; // 밀어낼 수 있는 블록용도로 쓸 것임


protected:

	/*
	속도 / 물풍선 / 물줄기
	*/
	UINT speedLvMin{};
	UINT speedLvMax{};

	UINT curIdleSpeedLv{};
	UINT speedLv{};

	UINT balloonCntMin{};
	UINT balloonCntMax{};
	UINT leftBalloonCnt{};

	UINT streamLvMin{};
	UINT streamLvMax{};
	UINT streamLv{};


protected:
	
	float captured_yUpdateTime = 0.f;
	float captured_ySpeed = 10.f;

	const float CAPTURED_Y_UPDATE_TICK = 1.f;
};

