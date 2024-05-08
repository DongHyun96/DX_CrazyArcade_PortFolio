#include "Framework.h"
#include "PlayerManager.h"


PlayerManager::PlayerManager()
{
	spawnPosMap =
	{
		{VILLAGE, {{1, 1}, {6, 0}, {14, 0}, {0, 12}, {7, 12}, {13, 11}}},
		{FACTORY, {{1, 0}, {13, 0}, {0, 6}, {0, 12}, {14, 12}, {7, 10}, {14, 6}, {7, 3}}},
		{FOREST, {{1, 1}, {8, 1}, {0, 4}, {1, 7}, {0, 12}, {5, 11}, {10, 9}, {10, 5}}},
		//{TEST_FIELD, {{1, 1}, {6, 0}, {14, 0}, {0, 12}, {7, 12}, {13, 11}}}
		//{TEST_FIELD, {{5, 5}, {6, 6}}}
	};

	P_DIR_KEYCODE[P2] =
	{
		{DIR_LEFT,	VK_LEFT},
		{DIR_RIGHT, VK_RIGHT},
		{DIR_UP,	VK_UP},
		{DIR_DOWN,	VK_DOWN}
	};

	P_BALLOON_KEYCODE[P2]	= VK_RSHIFT;
	P_ITEM_KEYCODE[P2]		= VK_HANJA;

	// Setting up characters

	p1CharacterData =
	{
		{BAZZI, new Player(BAZZI, P1)},
		{DAO,	new Player(DAO, P1)},
		{CAPPI, new Player(CAPPI, P1)},
		{MARID, new Player(MARID, P1)}
	};

	p2CharacterData =
	{
		{BAZZI, new Player(BAZZI, P2)},
		{DAO,	new Player(DAO, P2)},
		{CAPPI, new Player(CAPPI, P2)},
		{MARID, new Player(MARID, P2)}
	};

	for (UINT i = 0; i < ENEMY_CNT; i++)
		comEnemies.push_back(new Enemy(BAZZI));
}


PlayerManager::~PlayerManager()
{

	for (auto& p : p1CharacterData) delete p.second;
	for (auto& p : p2CharacterData) delete p.second;
	for (Character* c : comEnemies) delete c;

	wholePlayers.clear();
	p1CharacterData.clear();
	p2CharacterData.clear();
	comEnemies.clear();
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
		p1 = p1CharacterData[GM->P_SelectedCharacterMap()[P1]];
		p1->SetLabel("P1");
		p1->Init();

		p2 = p2CharacterData[GM->P_SelectedCharacterMap()[P2]];
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
		p1 = p1CharacterData[GM->P_SelectedCharacterMap()[P1]];
		p1->SetLabel("P1");
		p1->Init();

		vector<Util::Coord> spawnPos = spawnPosMap[GM->GetCurMapType()];
		random_shuffle(spawnPos.begin(), spawnPos.end());

		p1->SetSpawnPos(spawnPos[0]);

		wholePlayers.clear();
		wholePlayers.push_back(p1);

		for (UINT i = 0; i < comEnemies.size(); i++)
		{
			comEnemies[i]->Init();
			comEnemies[i]->SetLabel("Enemy" + i);
			comEnemies[i]->SetSpawnPos(spawnPos[1 + i]);
			wholePlayers.push_back(comEnemies[i]);
		}
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

	CheckAndHandleGameOver();
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
	P_ITEM_KEYCODE[P1]	  = VK_LCONTROL;
}


void PlayerManager::HandlePlayersGameOver()
{
	for (Character* player : wholePlayers)
		player->HandleGameOver();
}

void PlayerManager::HandlePlayerCollisions()
{
	for (Character* player : wholePlayers) // ��ü
	{
		switch (player->GetCharacterState()) 
			case C_CAPTURED: case C_RETURN_IDLE: case C_DEAD: continue;

		for (Character* target : wholePlayers) // �갡 ȿ�� �޴� ��
		{
			if (player == target)
				continue;

			//if (!player->GetBody()->AABBCollision(target->GetBody())) continue;
			if (!target->GetBody()->AABBCollision(player->GetBody()->GlobalPosition())) continue;
			
			if (target->GetCharacterState() == C_CAPTURED)
			{
				if (!target->IsCapturedCollidableWithOthers()) continue;

				if (player->GetPlayerType() == target->GetPlayerType())
					target->SetCharacterState(C_RETURN_IDLE);
				else
					target->SetCharacterState(C_DEAD);
			}
		}
	}
}

Util::Coord PlayerManager::GetApproximatedPlayerCoord(Character* character)
{
	Util::Coord exactCoord = GM->GetCollidedMapCellCoord(character->GetBody()->GlobalPosition());

	// �����¿� �밢 2ĭ �ݰ�(25ĭ) & �ش� coord�� ��ü�� ������
	vector<Util::Coord> candidates{};

	for (int i = -2; i <= 2; i++)
	{
		int y = exactCoord.y + i;

		if (y < 0 || y >= MAP_ROW) continue;

		for (int j = -2; j <= 2; j++)
		{
			int x = exactCoord.x + j;

			if (x < 0 || x >= MAP_COL) continue;

			Util::Coord coord = { (UINT)x, (UINT)y };

			Block* block = GM->GetBlockManager()->GetCoordBlock(coord);

			if (block) if (!block->IsHidable()) continue;
			
			if (Balloon::IsActiveBalloonOnCoord(coord)) continue;

			candidates.push_back(coord);
		}
	}
	
	if (candidates.empty()) return exactCoord;

	int randIdx = Util::GetRandom(0, (int)candidates.size() - 1);
	return candidates[randIdx];
}

void PlayerManager::CheckAndHandleGameOver()
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
			
			if (deathTimer >= DRAW_CHECK_TIME) // �� �÷��̾ ���� �� DEATH_CEHCK_TIME�� �Ѿ�� ���и� �������� �ð�
			{
				deathTimerTriggered = false;
				deathTimer = 0.f;

				if (p1->GetCharacterState() == C_DEAD && p2->GetCharacterState() == C_DEAD) // draw
					GM->GetGameScene()->SetGameEnd(DRAW);
				else if (p1->GetCharacterState() == C_DEAD)									// p2 win
					GM->GetGameScene()->SetGameEnd(P2_WIN);
				else if (p2->GetCharacterState() == C_DEAD)									// p1 win
					GM->GetGameScene()->SetGameEnd(P1_WIN);

				gameOverChecked = true;
			}
		}
		break;
	case PVE: // �÷��̾ ���� ��Ȳ, ��ǻ�Ͱ� ��� ���� ��Ȳ
	{

		bool comAllDead = true;

		for (Character* enemy : comEnemies)
		{
			if (enemy->GetCharacterState() != C_DEAD) comAllDead = false;
		}
		
		if (comAllDead || p1->GetCharacterState() == C_DEAD)
			deathTimerTriggered = true;

		if (deathTimerTriggered)
		{
			deathTimer += Time::Delta();

			if (deathTimer >= DRAW_CHECK_TIME)
			{
				deathTimerTriggered = false;
				deathTimer = 0.f;

				if (p1->GetCharacterState() == C_DEAD && comAllDead)	// Draw
					GM->GetGameScene()->SetGameEnd(DRAW);
				else if (p1->GetCharacterState() == C_DEAD)				// Com win
					GM->GetGameScene()->SetGameEnd(ENEMY_WIN);
				else if (comAllDead)									// Player Win
					GM->GetGameScene()->SetGameEnd(P1_WIN);

				gameOverChecked = true;
			}
		}
	}
		break;
	default:
		break;
	}
}
