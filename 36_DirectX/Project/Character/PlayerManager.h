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

public: /* �÷��̾�Type�� ���� input mapping KeyCodes */

	map<PlayerType, map<Direction, byte>> P_DIR_KEYCODE{};		// ����Ű Ű�ڵ� mapping
	map<PlayerType, byte>				  P_BALLOON_KEYCODE{};	// ��ǳ�� ���� Ű�ڵ� mapping
	map<PlayerType, byte>				  P_ITEM_KEYCODE{};		// ������ ��� Ű�ڵ� mapping

public:
	/* �� ���� ĳ���� ���� ���� ��ġ map */
	map<GameMap, vector<Util::Coord>> spawnPosMap{};


private: /* ���� �÷��̿� ����� Player�� Enemy */

	// ĳ���Ͱ� ���������� Character�� ����ִ� PlayerType���� ���а�����

	/* ���� �÷��̾� ���ձ� (PVP�� �� P1, P2 | PVE�� �� P1, comEnemies�� ����) */
	vector<Character*> wholePlayers{};

	Character* p1{};
	Character* p2{};


private: // �̸� �ʱ�ȭ�� �����͵�
	
	map<CharacterType, Character*> p1Characters{};
	map<CharacterType, Character*> p2Characters{};

	// comEnemies�� ������ ��� ���
	vector<Character*> comEnemies{};
	const UINT ENEMY_CNT{ 5 };


private:
	
	bool		deathTimerTriggered = false;
	float		deathTimer{};					// �� �÷��̾ ���� �� �����ؼ� 0.4�� �̳��� ��������� �����ϸ� draw�� ó��
	bool		gameOverChecked		= false;
	const float DRAW_CHECK_TIME		= 0.3f;

};
