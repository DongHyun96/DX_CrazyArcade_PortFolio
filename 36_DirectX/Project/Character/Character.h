#pragma once

class CharacterAnim;

#define SPEED_BASE 70.f


enum CharacterType
{
	BAZZI,
	DAO,
	CAPPI,
	MARID,
	RANDOM,
	CHARACTER_MAX
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

	C_DEAD,

	C_WIN
};

enum PlayerType
{
	P1,
	P2,
	COMPUTER,
	PLAYER_MAX
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
	Character(const CharacterType& cType, const PlayerType& playerType);

	virtual ~Character();

	virtual void Init();

	virtual void Update();
	virtual void Render();

	virtual void Move() = 0;

public:

	PlayerType GetPlayerType() const { return playerType; }

	void SetCharacterState(const CharacterState& state);
	CharacterState GetCharacterState() const { return mainState; }

	void SetVisible(const bool& visible) { this->visible = visible; }

	ColliderRect* GetBody() const { return body; }

	ColliderRect* GetPushCollider() const { return pushCollider; }

	Vector2 GetVelocity() const { return velocity; }

	UINT GetStreamLv() const { return streamLv; }

	bool AddLeftBalloonCnt(const UINT& addAmount = 1); // Balloon 회수 또는 Item Usage에 사용

	Direction GetCurFaceDir() const;

	void SetSpawnPos(const Util::Coord& spawnPos) { Util::SetTransformToGameBoard(body, spawnPos); }

	void SetGameOver();

	bool IsCapturedCollidableWithOthers() const { return is_captured_collidable_with_others; }

public: // Item Usage
	
	void SetConsumableItem(Item* consumable) { this->consumableItem = consumable; }
	Item* GetConsumableItem() const { return consumableItem; }

	bool IncreaseSpeed(bool increaseToMax = false);
	bool IncreaseStreamLv(bool increaseToMax = false);

public:
	
	void AddTimerBalloon(TimerBalloon* timerBalloon) { this->timerBalloons.push_back(timerBalloon); }

public:

	float GetSpeed() const { return SPEED_BASE * speedLv; }
	

protected: 

	virtual void HandleUseConsumableItem() = 0;
	bool UseConsumableItem();


private:

	void HandleBoundary();

	virtual void DeployBalloon() = 0;


public:
	virtual void Debug();
	void SetLabel(const string& label) { this->label = label; }





protected:

	bool visible{ true };

	void InitStat(const CharacterType& cType);

	void OnEndReturnToIdle()			{ SetCharacterState(C_IDLE); }
	void OnEndReturnToIdleOnGameOver()	{ SetCharacterState(C_WIN); }
	void OnCapturedEnd()				{ SetCharacterState(C_DEAD); }
	void OnDeadEnd()					{ visible = false; }

protected:

	PlayerType		playerType{};

	ColorBuffer*	colorBuffer{};

	ColliderRect*	body{};
	ColliderRect*	pushCollider{}; // 밀어낼 수 있는 블록용도로 쓸 것임

	Object*				shadow{};
	Object*				arrow{};
	map<bool, float>	arrowYDestMap{};
	bool				arrowYSwitched{};

	Vector2			velocity{};
	CharacterState	mainState{C_SPAWN};
	CharacterAnim*	actionHandler; // 실질적인 캐릭터 출력물 담당

	Item*			consumableItem{};

protected:

	vector<TimerBalloon*> timerBalloons{}; // 타이머 벌룬을 스폰시킬 때 여기로 해당 포인터를 받음

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

protected:
	string	label{};


protected: // 스폰 컬러 관련

	const Vector4 SPAWN_COLOR{ 0, 0, 0, 1 };
	float flicker{};
	bool flicked{};

protected: // Captured 되었을 때 실질적으로 플레이어상호간 충돌처리 가능한 시간대를 계산(너무 빨리 처리해버리면 이상함)

	const float CAPTURED_P_COLLIDE_START_TIME = 0.5f;
	float capturedTime = 0.f;
	bool is_captured_collidable_with_others{ false };

protected:

	//function<void()> NotifyCapturedEvent{}; // Enemy가 사용



};

