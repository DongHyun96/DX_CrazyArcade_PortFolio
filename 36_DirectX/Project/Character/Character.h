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

	C_DEAD,

	C_WIN
};

enum PlayerType
{
	P1,
	P2,
	COMPUTER
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

	bool AddLeftBalloonCnt(const UINT& addAmount = 1); // Balloon ȸ�� �Ǵ� Item Usage�� ���

	Direction GetCurFaceDir() const;

	void SetSpawnPos(const Util::Coord& spawnPos) { Util::SetTransformToGameBoard(body, spawnPos); }

public: // Item Usage
	
	void SetConsumableItem(Item* consumable) { this->consumableItem = consumable; }
	Item* GetConsumableItem() const { return consumableItem; }

	bool IncreaseSpeed(bool increaseToMax = false);
	bool IncreaseStreamLv(bool increaseToMax = false);

public:
	
	void AddTimerBalloon(TimerBalloon* timerBalloon) { this->timerBalloons.push_back(timerBalloon); }
	

protected: 

	virtual void HandleUseConsumableItem() = 0;
	bool UseConsumableItem();


private:

	void HandleBoundary();

	virtual void DeployBalloon() = 0;


public:
	void Debug();
	void SetLabel(const string& label) { this->label = label; }




protected:

	bool visible{ true };

	void InitStat(const CharacterType& cType);

	void OnEndReturnToIdle()	{ SetCharacterState(C_IDLE); }
	void OnCapturedEnd()		{ SetCharacterState(C_DEAD); }

protected:

	PlayerType		playerType{};

	ColorBuffer* colorBuffer{};

	ColliderRect*	body{};
	ColliderRect*	pushCollider{}; // �о �� �ִ� ��Ͽ뵵�� �� ����

	Object*			shadow{};
	Object*			arrow{};
	map<bool, float> arrowYDestMap{};
	bool arrowYSwitched{};

	Vector2			velocity{};
	CharacterState	mainState{C_SPAWN};
	CharacterAnim*	actionHandler; // �������� ĳ���� ��¹� ���

	Item*			consumableItem{};

protected:

	vector<TimerBalloon*> timerBalloons{}; // Ÿ�̸� ������ ������ų �� ����� �ش� �����͸� ����

protected:

	/*
	�ӵ� / ��ǳ�� / ���ٱ�
	*/
	UINT speedLvMin{};
	UINT speedLvMax{};

	UINT curIdleSpeedLv{}; // Idle ������ ���� speed�� �����ϱ� ���� ����
	UINT speedLv{}; // ����(Ż �� ����)�� speed

	UINT balloonCntMin{};
	UINT balloonCntMax{};
	UINT leftBalloonCnt{};

	UINT streamLvMin{};
	UINT streamLvMax{};
	UINT streamLv{}; // CurrentStreamLv

protected:
	string	label{};


protected: // ���� �÷� ����

	const Vector4 SPAWN_COLOR{ 0, 0, 0, 1 };
	float flicker{};
	bool flicked{};

};

