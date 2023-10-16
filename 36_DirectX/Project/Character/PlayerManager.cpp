#include "Framework.h"
#include "PlayerManager.h"


PlayerManager::PlayerManager()
{
	spawnPosMap =
	{
		{VILLAGE, {{1, 1}, {6, 0}, {14, 0}, {0, 12}, {7, 12}, {13, 11}}},
		{FACTORY, {}},
		{FOREST, {}}
	};

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


	P_DIR_KEYCODE[P2] =
	{
		{DIR_LEFT,	VK_LEFT},
		{DIR_RIGHT, VK_RIGHT},
		{DIR_UP,	VK_UP},
		{DIR_DOWN,	VK_DOWN}
	};

	P_BALLOON_KEYCODE[P2] = VK_RSHIFT;
	P_ITEM_KEYCODE[P2] = VK_HANJA;

	if (gameMode == PVP)
	{
		p1 = new Player(BAZZI, P1);
		p1->SetLabel("P1");

		p2 = new Player(BAZZI, P2);
		p2->SetLabel("P2");

		SetPlayers(p1, p2);

		vector<Util::Coord> spawnPos = spawnPosMap[GM->GetCurMapType()];

		random_shuffle(spawnPos.begin(), spawnPos.end());

		p1->SetSpawnPos(spawnPos[0]);
		p2->SetSpawnPos(spawnPos[1]);
	}
	else // PVE mode
	{

	}
}

PlayerManager::~PlayerManager()
{
	for (Character* player : wholePlayers)
		delete player;
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

void PlayerManager::SetPlayers(Character* p1, Character* p2)
{
	this->p1 = p1;
	this->p2 = p2;

	wholePlayers.clear();

	wholePlayers.push_back(p1);
	wholePlayers.push_back(p2);
}

void PlayerManager::SetPlayers(Character* p1, vector<Character*> enemies)
{
	this->p1 = p1;
	this->comEnemies = enemies;

	wholePlayers.clear();

	wholePlayers = enemies;
	wholePlayers.push_back(p1);
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
			
			if (deathTimer >= 0.3f) // 한 플레이어가 죽은 후 0.4초가 넘어가면 승패를 결정지을 시간
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
