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

	/* ���� ��忡 ���� p1 Ű�ڵ� ���� */
	void SetKeyCode(const GameMode& gameMode);

public: /* Getters */

	vector<Character*>& GetWholePlayers() { return wholePlayers; }

	Character*			GetP1() const { return p1; }
	Character*			GetP2() const { return p2; }
	vector<Character*>& GetComEnemies() { return comEnemies; }

public:

	/* GameOver�� Player���� GameOveró�� */
	void HandlePlayersGameOver();

private:
	/* GameOver üũ & GameOver�� �Ǿ��ٸ� GameOver handling�� ù ���� */
	void CheckAndHandleGameOver();

private:

	/* �÷��̾� ��ȣ�� �浹ó�� */
	void HandlePlayerCollisions();

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
	vector<Character*>	wholePlayers{};

	Character*			p1{};
	Character*			p2{};
	vector<Character*>	comEnemies{};

	const UINT			ENEMY_CNT{ 5 };

private: /* �̸� �ʱ�ȭ�� �� �÷��̾� ĳ���͵� data */
	
	map<CharacterType, Character*> p1CharacterData{};
	map<CharacterType, Character*> p2CharacterData{};

private: /* ���� ���� ó������ */
	
	bool		deathTimerTriggered{};			// ��� �� ���� �׾��� ��, deathTimer �ð� ������ ���� flag
	float		deathTimer{};					// �� �÷��̾ ���� �� �ð� �����ؼ� DEATH_CHECK_TIME �̳��� ��������� �����ϸ� draw�� ó��
	bool		gameOverChecked{};
	const float DRAW_CHECK_TIME = 0.3f;			// ��� �� �÷��̾ ���� ��, �ش� �ð� �̳��� ���� ���� ���� �÷��̾ ��� ����Ͽ��ٸ� drawó��

};
