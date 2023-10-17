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

public: // Players' keyCode

	map<PlayerType, map<Direction, byte>> P_DIR_KEYCODE{};
	map<PlayerType, byte> P_BALLOON_KEYCODE{};
	map<PlayerType, byte> P_ITEM_KEYCODE{};

public:

	map<GameMap, vector<Util::Coord>> spawnPosMap{};


private:

	// ĳ���Ͱ� ���������� Character�� ����ִ� PlayerType���� ���а�����

	vector<Character*> wholePlayers{};

	Character* p1{};
	Character* p2{};

	vector<Character*> comEnemies{};

private: // �̸� �ʱ�ȭ�� �����͵�
	
	map<CharacterType, Character*> p1Characters{};
	map<CharacterType, Character*> p2Characters{};

	// comEnemies�� ������ ��� ���


private:
	
	bool deathTimerTriggered = false;
	float deathTimer{ 0.f }; // �� �÷��̾ ���� �� �����ؼ� 0.4�� �̳��� ��������� �����ϸ� draw�� ó��
	bool gameOverChecked = false;

};
