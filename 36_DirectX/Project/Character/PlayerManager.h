#pragma once
class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

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

	void SetPlayers(Character* p1, Character* p2);
	void SetPlayers(Character* p1, vector<Character*> enemies);


private:

	void HandlePlayerCollisions();
	
	void CheckGameOver();

public: // Players' keyCode

	map<PlayerType, map<Direction, byte>> P_DIR_KEYCODE{};
	map<PlayerType, byte> P_BALLOON_KEYCODE{};
	map<PlayerType, byte> P_ITEM_KEYCODE{};

public:

	map<GameMap, vector<Util::Coord>> spawnPosMap{};


private:

	// 캐릭터가 누구인지는 Character가 들고있는 PlayerType으로 구분가능함

	vector<Character*> wholePlayers{};

	Character* p1{};
	Character* p2{};

	vector<Character*> comEnemies{};

private:
	
	bool deathTimerTriggered = false;
	float deathTimer{ 0.f }; // 한 플레이어가 죽은 뒤 측정해서 0.4초 이내로 상대팀원도 전멸하면 draw로 처리
	bool gameOverChecked = false;

};
