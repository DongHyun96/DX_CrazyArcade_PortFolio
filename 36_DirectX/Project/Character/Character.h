#pragma once

class CharacterAnim;

#define SPEED_BASE 70.f // ĳ���� speed lv�� ���� �⺻ base ���

/* ĳ���� ���� */
enum CharacterType
{
	BAZZI,
	DAO,
	CAPPI,
	MARID,
	RANDOM,
	CHARACTER_MAX
};

/* ĳ������ MainState */
enum CharacterState
{
	C_SPAWN,		// ���� ����

	C_IDLE,			// �⺻ Idle ����

	C_SPACECRAFT,	// ���ּ� ����
	C_OWL,			// �ξ��� ����
	C_TURTLE,		// �ź��� ����

	C_CAPTURED,		// ��ǳ���� ���� ����

	C_RETURN_IDLE,	// ��ǳ�� ���� �Ǵ� Ż �Ϳ��� ������ Idle�� ���ư��� �ִ� ����

	C_DEAD,

	C_WIN
};

/* ĳ������ PlayerType - P1, P2, Computer���� �����ϱ� ���� */
enum PlayerType
{
	P1,
	P2,
	COMPUTER,
	PLAYER_MAX
};


/* Ż �Ͱ� captured �Ǿ��� ��(��� ĳ������ �ӵ��� ����)�� Common Speed level */
static struct CommonSpeedLv
{
	static const UINT CAPTURED_SPEED_LV		= 1;
	static const UINT SPACE_SPEED_LV		= 10;
	static const UINT OWL_SPEED_LV			= 6;
	static const UINT TURTLE_SPEED_LV		= 2;
};

class Character : public ColliderHolder
{
public:
	Character(const CharacterType& cType, const PlayerType& playerType);
	virtual ~Character();

	virtual void Init();

	virtual void Update();
	virtual void Render();

private: 
	/*
	Basic move pure-virtual method
	�ڽ� �ܰ迡�� Player�� input�� ����, Enemy�� EnemyAI�� ���� ����
	*/
	virtual void Move() = 0;

public: /* Getters, Setters, Adders */

	ColliderRect*	GetBody() const { return body; }
	ColliderRect*	GetPushCollider() const { return pushCollider; }

	void			SetVisible(const bool& visible) { this->visible = visible; }

	PlayerType		GetPlayerType() const { return playerType; }

	void			SetCharacterState(const CharacterState& state);
	CharacterState	GetCharacterState() const { return mainState; }

	void			SetSpawnPos(const Util::Coord& spawnPos) { Util::SetTransformToGameBoard(body, spawnPos); }

	Vector2			GetVelocity() const { return velocity; }
	float			GetSpeed() const { return SPEED_BASE * speedLv; }

	UINT			GetStreamLv() const { return streamLv; }

	bool			AddLeftBalloonCnt(const UINT& addAmount = 1); // Balloon ȸ�� & ��ǳ�� ������ ȹ�� �� ���

	Direction		GetCurFaceDir() const;

	bool			IsCapturedCollidableWithOthers() const { return is_captured_collidable_with_others; }
	
	void			SetConsumableItem(Item* consumable) { this->consumableItem = consumable; }
	Item*			GetConsumableItem() const { return consumableItem; }


public: /* ���� ��ȭ methods */

	bool IncreaseSpeed(bool increaseToMax = false);
	bool IncreaseStreamLv(bool increaseToMax = false);

public: 
	/* �ڽ��� �ʵ忡 spawn�� timerballoon ���� */
	void AddTimerBalloon(TimerBalloon* timerBalloon) { this->timerBalloons.push_back(timerBalloon); }

public: 
	/* GameOver handling */
	void HandleGameOver();

protected: /* �Ҹ� ������ ��� ���� */

	virtual void	HandleUseConsumableItem() = 0;
	bool			UseConsumableItem();

private:
	/* Map boundary �浹ó�� */
	void HandleBoundary();

private:
	/* ��ǳ�� ���� method */
	virtual void DeployBalloon() = 0;

public: /* Debugging ���� */
	virtual void	Debug();
	void			SetLabel(const string& label) { this->debugLabel = label; }

protected: 
	/* Initialize stats */
	void InitStat(const CharacterType& cType);

protected: /* Event handling methods */

	void OnEndReturnToIdle()			{ SetCharacterState(C_IDLE); }
	void OnEndReturnToIdleOnGameOver()	{ SetCharacterState(C_WIN); }
	void OnCapturedEnd()				{ SetCharacterState(C_DEAD); }
	void OnDeadEnd()					{ visible = false; }

private: /* Update methods */

	void UpdatePlayerArrow();
	void UpdateBasedOnMainCharacterState(OUT bool& continueCharacterUpdate);


/***************************************************************************************************
*                                          Member variables                                        *
****************************************************************************************************/
protected: 
	/* Visibility */
	bool visible{ true };

protected: /* PlayerType, MainState */

	PlayerType		playerType{}; // PlayerType - P1, P2, Enemy(Computer)
	CharacterState	mainState{C_SPAWN};

protected: /* Colliders */
	ColliderRect*	body{};			// Main body collider
	ColliderRect*	pushCollider{}; // �о �� �ִ� ��Ͽ뵵�� �� ����

protected: /* ĳ���� �׸��� �� ȭ��ǥ */
	Object*				shadow{};
	Object*				arrow{};
	map<bool, float>	arrowYDestMap{};
	bool				arrowYSwitched{};

protected: 
	/* Character velocity */
	Vector2 velocity{};

protected: 
	/* �������� ĳ���� �ִϸ��̼� ��������Ʈ ��� ��� */
	CharacterAnim* actionHandler{};

protected:	
	/* �Ҹ�ǰ ������(�ٴ�, ��Ʈ ��) */
	Item* consumableItem{};

protected:
	/* 
	* ���� �ʵ忡 ������ timerballoon���� pointer ����
	* ��ǳ���� ���� ��(DeployBalloon) �ڽ��� ���� timerBallon�� �ϳ��� �����Ѵٸ� timerBalloon�� ��ġ�� �뵵�� ���
	*/
	vector<TimerBalloon*> timerBalloons{};

protected: /* ���� ���� (�ӵ�, ��ǳ�� ����, ���ٱ� ����) */
	
	UINT speedLvMin{};
	UINT speedLvMax{};

	UINT curIdleSpeedLv{};	// ������ Idle ������ ���� speed lv�� ����
	UINT speedLv{};			// ����(Ż �� ����)�� speed lv

	UINT balloonCntMin{};
	UINT balloonCntMax{};
	UINT leftBalloonCnt{};

	UINT streamLvMin{};
	UINT streamLvMax{};
	UINT streamLv{};		

protected: /* ���� �÷� ���� */

	ColorBuffer*	spawnColorBuffer{}; // ���� �� ����� colorBuffer
	float			flicker{};
	bool			flicked{};
	const Vector4	SPAWN_COLOR = { 0, 0, 0, 1 };

protected:
	/*
	* Captured �Ǿ��� �� �÷��̾� ��ȣ�� �浹ó���� �ٷ� ó���ϸ� �����
	* Captured �Ǿ��� �� ���� term�� �� �� �浹ó�� ����
    */

	const float CAPTURED_P_COLLIDE_START_TIME = 0.5f;
	float		capturedTime = 0.f;
	bool		is_captured_collidable_with_others{};

protected: 
	/* Debug label */
	string	debugLabel{};

};

