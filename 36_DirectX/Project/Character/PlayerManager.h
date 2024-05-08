#pragma once
/* CONCRETE CLASS */
class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

	void Init();

	void Update();
	void Render();

public:

	/* 게임 모드에 따른 p1 키코드 변경 */
	void SetKeyCode(const GameMode& gameMode);

public: /* Getters */

	vector<Character*>& GetWholePlayers() { return wholePlayers; }

	Character*			GetP1() const { return p1; }
	Character*			GetP2() const { return p2; }
	vector<Character*>& GetComEnemies() { return comEnemies; }

public:

	/* GameOver시 Player들의 GameOver처리 */
	void HandlePlayersGameOver();

private:
	/* GameOver 체크 & GameOver가 되었다면 GameOver handling의 첫 시작 */
	void CheckAndHandleGameOver();

private:

	/* 플레이어 상호간 충돌처리 */
	void HandlePlayerCollisions();

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
	vector<Character*>	wholePlayers{};

	Character*			p1{};
	Character*			p2{};
	vector<Character*>	comEnemies{};

	const UINT			ENEMY_CNT{ 5 };

private: /* 미리 초기화해 둔 플레이어 캐릭터들 data */
	
	map<CharacterType, Character*> p1CharacterData{};
	map<CharacterType, Character*> p2CharacterData{};

private: /* 게임 오버 처리관련 */
	
	bool		deathTimerTriggered{};			// 어느 한 명이 죽었을 때, deathTimer 시간 측정을 위한 flag
	float		deathTimer{};					// 한 플레이어가 죽은 뒤 시간 측정해서 DEATH_CHECK_TIME 이내로 상대팀원도 전멸하면 draw로 처리
	bool		gameOverChecked{};
	const float DRAW_CHECK_TIME = 0.3f;			// 어느 한 플레이어가 죽은 뒤, 해당 시간 이내로 현재 게임 내에 플레이어가 모두 사망하였다면 draw처리

};
