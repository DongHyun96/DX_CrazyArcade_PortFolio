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

private:

	void SetPlayers(Character* p1, Character* p2);
	void SetPlayers(Character* p1, vector<Character*> enemies);

private:

	void HandlePlayerCollisions();

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
};
