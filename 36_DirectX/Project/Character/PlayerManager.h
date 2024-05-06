#pragma once
class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

	void Init();

	void Update();
	void Render();

public:

	void SetKeyCode(const GameMode& gameMode);

	vector<Character*>& GetWholePlayers() { return wholePlayers; }

	Character* GetP1() const { return p1; }
	Character* GetP2() const { return p2; }

	vector<Character*>& GetComEnemies() { return comEnemies; }

	void SetGameOver();

private:

	void HandlePlayerCollisions();
	
	void CheckGameOver();

public: /* 플레이어Type에 따른 input mapping KeyCodes */

	map<PlayerType, map<Direction, byte>> P_DIR_KEYCODE{};		// 방향키 키코드 mapping
	map<PlayerType, byte>				  P_BALLOON_KEYCODE{};	// 물풍선 놓기 키코드 mapping
	map<PlayerType, byte>				  P_ITEM_KEYCODE{};		// 아이템 사용 키코드 mapping

public:
	/* 각 맵의 캐릭터 스폰 가능 위치 map */
	map<GameMap, vector<Util::Coord>> spawnPosMap{};


private: /* 게임 플레이에 사용할 Player와 Enemy */

	// 캐릭터가 누구인지는 Character가 들고있는 PlayerType으로 구분가능함

	/* 전제 플레이어 집합군 (PVP일 때 P1, P2 | PVE일 때 P1, comEnemies로 구성) */
	vector<Character*> wholePlayers{};

	Character* p1{};
	Character* p2{};


private: // 미리 초기화한 데이터들
	
	map<CharacterType, Character*> p1Characters{};
	map<CharacterType, Character*> p2Characters{};

	// comEnemies는 무조건 배찌만 사용
	vector<Character*> comEnemies{};
	const UINT ENEMY_CNT{ 5 };


private:
	
	bool		deathTimerTriggered = false;
	float		deathTimer{};					// 한 플레이어가 죽은 뒤 측정해서 0.4초 이내로 상대팀원도 전멸하면 draw로 처리
	bool		gameOverChecked		= false;
	const float DRAW_CHECK_TIME		= 0.3f;

};
