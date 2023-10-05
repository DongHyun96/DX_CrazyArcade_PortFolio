#pragma once

class CharacterAnim;

#define SPEED_BASE 50.f

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

class Character : public Transform
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

	void SetCharacterState(const CharacterState& state) { this->mainState = state; }
	void SetVisible(const bool& visible) { this->visible = visible; }

	ColliderRect* GetBody() const { return body; }

	ColliderRect* GetPushCollider() const { return pushCollider; }

	Vector2 GetVelocity() const { return velocity; }

private:
	void HandleBoundary();

protected:

	ColorBuffer* colorBuffer{};
	bool visible{ true };

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
	UINT balloonCntMin{};
	UINT balloonCntMax{};
	UINT streamLvMin{};
	UINT streamLvMax{};

	UINT speedLv{ 1 };
	UINT balloonCnt{ 1 };
	UINT streamLv{ 1 };

};
