#include "Framework.h"
#include "PlayerManager.h"


PlayerManager::PlayerManager()
{
	spawnPosMap =
	{
		{VILLAGE, {{1, 1}, {6, 0}, {14, 0}, {0, 12}, {7, 12}, {13, 11}}},
		{FACTORY, {{1, 0}, {13, 0}, {0, 6}, {0, 12}, {14, 12}, {7, 10}, {14, 6}, {7, 3}}},
		{FOREST, {{1, 1}, {8, 1}, {0, 4}, {1, 7}, {0, 12}, {5, 11}, {10, 9}, {10, 5}}}
	};

	P_DIR_KEYCODE[P2] =
	{
		{DIR_LEFT,	VK_LEFT},
		{DIR_RIGHT, VK_RIGHT},
		{DIR_UP,	VK_UP},
		{DIR_DOWN,	VK_DOWN}
	};

	P_BALLOON_KEYCODE[P2] = VK_RSHIFT;
	P_ITEM_KEYCODE[P2] = VK_HANJA;

	// Setting up characters

	p1Characters =
	{
		{BAZZI, new Player(BAZZI, P1)},
		//{DAO, new Player(DAO, P1)},
		//{CAPPI, new Player(CAPPI, P1)},
		//{MARID, new Player(MARID, P1)},
	};

	p2Characters =
	{
		{BAZZI, new Player(BAZZI, P2)},
		//{DAO, new Player(DAO, P2)},
		//{CAPPI, new Player(CAPPI, P2)},
		//{MARID, new Player(MARID, P2)},
	};

	// TODO: enemyCharacters �ʱ�ȭ

}


PlayerManager::~PlayerManager()
{
	for (Character* player : wholePlayers)
		delete player;
}

void PlayerManager::Init()
{
	GameMode gameMode = GM->GetGameMode();

	P_DIR_KEYCODE[P1] =
	{
		{DIR_LEFT,	gameMode == PVP ? 'D' : VK_LEFT},
		{DIR_RIGHT, gameMode == PVP ? 'G' : VK_RIGHT},
		{DIR_UP,	gameMode == PVP ? 'R' : VK_UP},
		{DIR_DOWN,	gameMode == PVP ? 'F' : VK_DOWN}
	};

	P_BALLOON_KEYCODE[P1] = gameMode == PVP ? VK_LSHIFT : VK_SPACE;
	P_ITEM_KEYCODE[P1] = VK_LCONTROL;


	if (gameMode == PVP) // TODO p1�� p2 ����ĳ���� Ÿ�� ��������
	{
		p1 = p1Characters[GM->P_SelectedCharacterMap()[P1]];
		p1->SetLabel("P1");
		p1->Init();

		p2 = p2Characters[GM->P_SelectedCharacterMap()[P2]];
		p2->SetLabel("P2");
		p2->Init();

		vector<Util::Coord> spawnPos = spawnPosMap[GM->GetCurMapType()];

		random_shuffle(spawnPos.begin(), spawnPos.end());

		p1->SetSpawnPos(spawnPos[0]);
		p2->SetSpawnPos(spawnPos[1]);

		wholePlayers.clear();

		wholePlayers.push_back(p1);
		wholePlayers.push_back(p2);

	}
	else // PVE mode
	{

	}

	deathTimerTriggered = false;
	deathTimer = 0.f;
	gameOverChecked = false;

}

void PlayerManager::Update()
{
	for (Character* player : wholePlayers)
		player->Update();

	HandlePlayerCollisions();

	CheckGameOver();
}

void PlayerManager::Render()
{
	for (Character* player : wholePlayers)
		player->Render();
}

void PlayerManager::SetKeyCode(const GameMode& gameMode)
{
	P_DIR_KEYCODE[P1] =
	{
		{DIR_LEFT,	gameMode == PVP ? 'D' : VK_LEFT},
		{DIR_RIGHT, gameMode == PVP ? 'G' : VK_RIGHT},
		{DIR_UP,	gameMode == PVP ? 'R' : VK_UP},
		{DIR_DOWN,	gameMode == PVP ? 'F' : VK_DOWN}
	};

	P_BALLOON_KEYCODE[P1] = gameMode == PVP ? VK_LSHIFT : VK_SPACE;
	P_ITEM_KEYCODE[P1] = VK_LCONTROL;
}


void PlayerManager::SetGameOver()
{
	for (Character* player : wholePlayers)
		player->SetGameOver();
}

void PlayerManager::HandlePlayerCollisions()
{
	for (Character* player : wholePlayers)
	{
		switch (player->GetCharacterState()) 
			case C_CAPTURED: case C_RETURN_IDLE: case C_DEAD: continue;

		for (Character* target : wholePlayers)
		{
			if (player == target)
				continue;

			if (!player->GetBody()->AABBCollision(target->GetBody())) continue;
			
			if (target->GetCharacterState() == C_CAPTURED)
			{
				if (player->GetCharacterState() == target->GetCharacterState())
					target->SetCharacterState(C_RETURN_IDLE);
				else
					target->SetCharacterState(C_DEAD);
			}
		}
	}
}

void PlayerManager::CheckGameOver()
{
	if (gameOverChecked) return;

	switch (GM->GetGameMode())
	{
	case PVP:

		for (Character* player : wholePlayers)
		{
			if (player->GetCharacterState() == C_DEAD)
			{
				deathTimerTriggered = true;
				break;
			}
		}

		if (deathTimerTriggered)
		{
			deathTimer += Time::Delta();
			
			if (deathTimer >= 0.3f) // �� �÷��̾ ���� �� 0.4�ʰ� �Ѿ�� ���и� �������� �ð�
			{
				deathTimerTriggered = false;
				deathTimer = 0.f;

				if (p1->GetCharacterState() == C_DEAD && p2->GetCharacterState() == C_DEAD)
				{
					// draw
					GM->GetGameScene()->SetGameEnd(DRAW);
				}
				else if (p1->GetCharacterState() == C_DEAD)
				{
					// p2 win
					GM->GetGameScene()->SetGameEnd(P2_WIN);
				}
				else if (p2->GetCharacterState() == C_DEAD)
				{
					// p1 win
					GM->GetGameScene()->SetGameEnd(P1_WIN);
				}

				gameOverChecked = true;
			}
		}

		break;
	case PVE:
		break;
	default:
		break;
	}
}
