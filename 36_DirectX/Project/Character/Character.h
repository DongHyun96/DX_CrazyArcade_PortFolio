#pragma once

class CharacterAnim;

#define SPEED_BASE 70.f // 캐릭터 speed lv에 곱할 기본 base 배수

/* 캐릭터 종류 */
enum CharacterType
{
	BAZZI,
	DAO,
	CAPPI,
	MARID,
	RANDOM,
	CHARACTER_MAX
};

/* 캐릭터의 MainState */
enum CharacterState
{
	C_SPAWN,		// 스폰 상태

	C_IDLE,			// 기본 Idle 상태

	C_SPACECRAFT,	// 우주선 상태
	C_OWL,			// 부엉이 상태
	C_TURTLE,		// 거북이 상태

	C_CAPTURED,		// 물풍선에 갇힌 상태

	C_RETURN_IDLE,	// 물풍선 상태 또는 탈 것에서 내려서 Idle로 돌아가고 있는 상태

	C_DEAD,

	C_WIN
};

/* 캐릭터의 PlayerType - P1, P2, Computer인지 구분하기 위함 */
enum PlayerType
{
	P1,
	P2,
	COMPUTER,
	PLAYER_MAX
};


/* 탈 것과 captured 되었을 때(모든 캐릭터의 속도가 동일)의 Common Speed level */
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
	자식 단계에서 Player는 input에 따라, Enemy는 EnemyAI에 따라 구현
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

	bool			AddLeftBalloonCnt(const UINT& addAmount = 1); // Balloon 회수 & 물풍선 아이템 획득 시 사용

	Direction		GetCurFaceDir() const;

	bool			IsCapturedCollidableWithOthers() const { return is_captured_collidable_with_others; }
	
	void			SetConsumableItem(Item* consumable) { this->consumableItem = consumable; }
	Item*			GetConsumableItem() const { return consumableItem; }


public: /* 스탯 강화 methods */

	bool IncreaseSpeed(bool increaseToMax = false);
	bool IncreaseStreamLv(bool increaseToMax = false);

public: 
	/* 자신이 필드에 spawn한 timerballoon 저장 */
	void AddTimerBalloon(TimerBalloon* timerBalloon) { this->timerBalloons.push_back(timerBalloon); }

public: 
	/* GameOver handling */
	void HandleGameOver();

protected: /* 소모 아이템 사용 관련 */

	virtual void	HandleUseConsumableItem() = 0;
	bool			UseConsumableItem();

private:
	/* Map boundary 충돌처리 */
	void HandleBoundary();

private:
	/* 물풍선 놓기 method */
	virtual void DeployBalloon() = 0;

public: /* Debugging 관련 */
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
	ColliderRect*	pushCollider{}; // 밀어낼 수 있는 블록용도로 쓸 것임

protected: /* 캐릭터 그림자 및 화살표 */
	Object*				shadow{};
	Object*				arrow{};
	map<bool, float>	arrowYDestMap{};
	bool				arrowYSwitched{};

protected: 
	/* Character velocity */
	Vector2 velocity{};

protected: 
	/* 실질적인 캐릭터 애니메이션 스프라이트 출력 담당 */
	CharacterAnim* actionHandler{};

protected:	
	/* 소모품 아이템(바늘, 다트 등) */
	Item* consumableItem{};

protected:
	/* 
	* 게임 필드에 스폰된 timerballoon들의 pointer 저장
	* 물풍선을 놓을 때(DeployBalloon) 자신이 놓은 timerBallon이 하나라도 존재한다면 timerBalloon을 터치는 용도로 사용
	*/
	vector<TimerBalloon*> timerBalloons{};

protected: /* 스탯 관련 (속도, 물풍선 갯수, 물줄기 스탯) */
	
	UINT speedLvMin{};
	UINT speedLvMax{};

	UINT curIdleSpeedLv{};	// 마지막 Idle 상태일 때의 speed lv를 저장
	UINT speedLv{};			// 현재(탈 것 포함)의 speed lv

	UINT balloonCntMin{};
	UINT balloonCntMax{};
	UINT leftBalloonCnt{};

	UINT streamLvMin{};
	UINT streamLvMax{};
	UINT streamLv{};		

protected: /* 스폰 컬러 관련 */

	ColorBuffer*	spawnColorBuffer{}; // 스폰 시 사용할 colorBuffer
	float			flicker{};
	bool			flicked{};
	const Vector4	SPAWN_COLOR = { 0, 0, 0, 1 };

protected:
	/*
	* Captured 되었을 때 플레이어 상호간 충돌처리를 바로 처리하면 어색함
	* Captured 되었을 때 일정 term을 준 뒤 충돌처리 진행
    */

	const float CAPTURED_P_COLLIDE_START_TIME = 0.5f;
	float		capturedTime = 0.f;
	bool		is_captured_collidable_with_others{};

protected: 
	/* Debug label */
	string	debugLabel{};

};

