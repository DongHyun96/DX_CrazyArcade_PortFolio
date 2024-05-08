#include "Framework.h"
#include "Enemy.h"



Enemy::Enemy(const CharacterType& cType)
	:Character(cType, COMPUTER)
{
	//NotifyCapturedEvent = bind(&Enemy::OnCaptured, this);
}

Enemy::~Enemy()
{
}

void Enemy::SetPathToRescueMission(const pair<stack<Util::Coord>, set<Util::Coord>>& rescue_path_visited_pair, Character* rescueTarget)
{
	targetState			= RESCUE_PEER;

	this->path			= rescue_path_visited_pair.first;
	this->visited		= rescue_path_visited_pair.second;
	this->rescueTarget	= rescueTarget;
}


void Enemy::Move()
{
	if (mainState == C_CAPTURED)
	{
		// 0.5�ʿ� �� �� 2�� �� �ѹ� �� ȣ�����־� �ѹ� �� ���� ��û��
		if (requestResqueTwice) return;

		capturedTime += Time::Delta();

		if (!requestResqueOnce && capturedTime >= RESCUE_CALL_TIME_ONCE)
		{
			RequestRescue();
			requestResqueOnce = true;
			return;
		}

		if (capturedTime < RESCUE_CALL_TIME_TWICE) return;

		requestResqueTwice = true;
		capturedTime = 0.f;

		RequestRescue();

		return;
	}
	else
	{
		requestResqueOnce = false;
		requestResqueTwice = false;
		capturedTime = 0.f;
	}

	myCoord = GM->GetCollidedMapCellCoord(body->GlobalPosition());

	velocity = Vector2();

	UpdateState();

	if (path.empty()) return;

	Vector2 destination = Util::ConvertBoardIdxToWorldPos(path.top());
	Vector2 dir = destination - body->translation;

	if (abs(dir.x) < abs(dir.y)) dir.x = 0.f;
	else dir.y = 0.f;


	if (dir.Length() < 1.f)// destination reached�� �Ǵ� -> ���⼭ ��� �缳�� Ʈ���Ű� �����ؾ��� & path�� ����� ���� �ѹ� �����ؾ� ��
	{
		body->translation = destination;
		path.pop();
		blockedTime = 0.f;
	}
	else
	{
		velocity = dir.GetNormal() * SPEED_BASE * speedLv;
		body->translation += velocity * Time::Delta();

		blockedTime += Time::Delta();

		if (blockedTime >= BLOCKED_TIME_LIMIT) // Path�� ���� �����ְ� ���ڸ��� ��� �ӹ� �� ��� ���������̶� �Ǵ� -> �ٽ� None���� ���ư��� ���Ǵ�
		{
			path = {};
			visited.clear();
			targetState = NONE;
			blockedTime = 0.f;
		}
	}
	
}

void Enemy::HandleUseConsumableItem()
{
}

void Enemy::DeployBalloon()
{
}

void Enemy::Init()
{
	Character::Init();

	targetState = NONE;

	path = {};
	visited.clear();
	myCoord = {};

	safeZoneWaitTime = 0.f;
	blockedTime = 0.f;

	player_approach_lv = 0;

	rescueTarget = nullptr;

	requestResqueOnce = false;
	requestResqueTwice = false;
	capturedTime = 0.f;
}

void Enemy::UpdatePath(const Util::Coord& dest)
{
	auto path_visited	= AStarPathFinder::GetPath(myCoord, dest, mainState == C_SPACECRAFT);
	path				= path_visited.first;
	visited				= path_visited.second;
}

void Enemy::UpdateState()
{
	// path�� empty�̸� �����ߴٴ� ���

	//TargetState prevState = targetState;
	//if (path.empty()) targetState = NONE;

	switch (targetState)
	{
	case Enemy::PLAYER:
		if (path.size() <= player_approach_lv) // �����ϰ� ������ approach_lv�� �����ߴٸ� ��ο� �����ߴٰ� �Ǵ�
		{
			DeployBalloonManually();
			targetState = NONE;
		}
		break;
	case Enemy::BALLOON_D_POS: // ��ǳ���� ���� �� ���� ����� safe_zone���� ������
		if (path.empty())
		{
			DeployBalloonManually();
			targetState = SAFE_ZONE;

			// �÷��̾� ��ġ�� path Update �õ�
			Util::Coord pCurCoord = GM->GetCollidedMapCellCoord(PM->GetP1()->GetBody()->GlobalPosition());
			UpdatePath(pCurCoord);
			
			if (!path.empty())
			{
				// Ȯ�������� �÷��̾�� �������� ���� ��� X �̰� ���� ���� ���ο� ����ݰ� �����ؼ� ���ο� safezone���� �̵��ϴ°� �������� ����
			}
			else
			{
				// ���� �� -> �ٷ� ���� ����� safezone���� �̵�
				bool safeCoordExist{};
				Util::Coord safeCoord = GetSafeCoord(visited, safeCoordExist);

				if (!safeCoordExist)
				{
					targetState = NONE;
					break;
				}

				UpdatePath(safeCoord);
				targetState = SAFE_ZONE;
			}
		}
		break;
	case Enemy::SAFE_ZONE:
		if (path.empty())
		{
			safeZoneWaitTime += Time::Delta();
			
			if (Balloon::IsPreDangerZone(myCoord)) // ���� �ڽ��� ��ġ�� �� ������ ������ �ڸ��� �ٸ� �ڸ��� �̵�
			{
				safeZoneWaitTime = 0.f;
				targetState = NONE;
			}

			if (safeZoneWaitTime < SAFE_ZONE_WAIT_TIME) return; // safe_zone���� 3�ʰ� ����� �� �ٽñ� ��ã��

			safeZoneWaitTime = 0.f;
			targetState = NONE;
		}
		break;
	case Enemy::RESCUE_PEER:
		
		if (rescueTarget->GetCharacterState() != C_CAPTURED || path.empty()) // �̹� �������ų� �̹� ���� ����
		{
			path = {};
			visited.clear();
			targetState = NONE;
		}
		break;
	case Enemy::NONE: // None�� ������ �ٷ� ���� ��ȯ �õ�
	{
		// �÷��̾��� approximate ��ġ�� path Update �õ�
		Util::Coord approximate_player_coord = PM->GetApproximatedPlayerCoord(PM->GetP1());
		UpdatePath(approximate_player_coord);

		if (path.empty()) // �÷��̾������ ���ް�ΰ� ���� ��
		{
			// ��ǳ���� ���� ��ġ �Ǵ�
			vector<Util::Coord> deployable = GetDeployableCoords(visited);

			// ��ǳ���� ���� �ڸ��� ���ٸ� ó������ ���ư�
			if (deployable.empty()) break; 

			// ��ǳ���� ���� �ڸ� �� �̻����� �ڸ��� ����
			Util::Coord targetCoord = GetIdealDeployCoord(deployable);
			
			// ��ǳ���� �����ڸ��� ��� ����
			UpdatePath(targetCoord);
			
			targetState = BALLOON_D_POS;
		}
		else if (path.size() > 10) // �÷��̾������ ���ް�ΰ� ����� ������ �ʹ� �� ��
		{
			targetState = PLAYER;
		}
		else // �÷��̾� ��ġ���� ����
		{
			player_approach_lv = Util::GetRandom(PLAYER_APPROACH_MIN, PLAYER_APPROACH_MAX);
			targetState = PLAYER;
		}
	}
		break;
	default:
		break;
	}
}

void Enemy::DeployBalloonManually()
{
	switch (mainState)
	{
	case C_SPAWN: case C_CAPTURED: case C_RETURN_IDLE: case C_DEAD: case C_WIN: return;
	}

	if (!timerBalloons.empty()) // Ÿ�̸� ������ ���õǾ����� ��
	{

		// Ÿ�̸� ������ �ѹ��� ��ħ
		for (TimerBalloon* t_balloon : timerBalloons)
		{
			if (!t_balloon) continue;

			t_balloon->Explode();
		}

		timerBalloons.clear();

		return;
	}

	if (leftBalloonCnt <= 0) return;

	if (GM->GetBalloonManager()->Spawn(myCoord, this))
	{
		//SOUND->Play("BalloonDeploy", 1.f);
		leftBalloonCnt--;
	}
}

void Enemy::RequestRescue() // ó�� �ѹ� ȣ���ϰ� ���� �� �ѹ� �� ȣ���غ� (�� �ι�)
{
	/* ������� �Ÿ������� ���� */
	set<pair<UINT, Character*>> sortedByDist{};

	for (Character* target : GM->GetPlayerManager()->GetComEnemies())
	{
		Util::Coord targetCoord = GM->GetCollidedMapCellCoord(target->GetBody()->GlobalPosition());
		UINT dist = Util::GetDist(myCoord, targetCoord);

		sortedByDist.insert(make_pair(dist, target));
	}

	for (const auto& p : sortedByDist) // ���� ����� �Ÿ��� �����ϴ� ���� ��
	{
		Character* target = p.second;

		// ���� ���ᰡ ������ �� ���� ��Ȳ�̸� �Ѿ
		if (target->GetCharacterState() == C_CAPTURED || target->GetCharacterState() == C_DEAD)
			continue;

		// ���� ��������� ��ΰ� �����ϴ��� üũ, targetCoord -> ���� ������ ��ġ
		Util::Coord targetCoord = GM->GetCollidedMapCellCoord(target->GetBody()->GlobalPosition());

		// Captured���� �� �ڽ����κ��� ��������� ��ΰ� �����ϴ��� üũ�� (�� path�� Update�غ�)
		UpdatePath(targetCoord);

		// �ش��ϴ� ��ΰ� ���ٸ� ���� ����� �ٽ� �õ�
		if (path.empty()) continue;

		// for loop�� ���� ���ᰡ ��ΰ� �����ϴ� ���� ����� ���� -> ���� ã�� ��θ� ��Ʈ��ŷ�Ͽ� ������ ��û�� ������ path�� �־���
		stack<Util::Coord> rescuerPath{}; // ������ ���
		
		// ���� ã�� ��θ� ������ �־��ֵ�, ������ ����� ������ ���� ��ǥ�� �־��ְ�, ����� ����(rescuer�ڱ��ڽ��� ����ġ) �κ��� �ϳ� ����� ��

		rescuerPath.push(myCoord);

		while (!path.empty())
		{
			rescuerPath.push(path.top());
			path.pop();
		}

		rescuerPath.pop();

		// ������ targetState�� RESCUE_PEER�� �ٲٰ� path�� �� �ڽ��� ���Ϸ� ���� path�� ����
		Enemy* peer = dynamic_cast<Enemy*>(target);
		peer->SetPathToRescueMission(make_pair(rescuerPath, visited), this);

		// ������û �� �� �ڽ��� path, visited, targetState �ʱ�ȭ
		visited.clear();
		path = {};
		targetState = NONE;

		break;
	}

	
}

vector<Util::Coord> Enemy::GetDeployableCoords(const set<Util::Coord>& visited)
{
	vector<Util::Coord> deployable{};

	for (Util::Coord coord : visited)
	{
		if (IsDeployable(coord, visited)) deployable.push_back(coord);
	}

	return deployable;
}

bool Enemy::IsDeployable(const Util::Coord& coord, const set<Util::Coord>& visited)
{
	static vector<int> dx = { 0, 0, -1, 1 };
	static vector<int> dy = { 1, -1, 0, 0 };

	// �������� ���� ��ǥ���� ������ ����
	set<Util::Coord> unsafeCoords{};
	unsafeCoords.insert(coord);
	
	for (UINT i = 0; i < 4; i++)
	{
		int x = coord.x;
		int y = coord.y;

		for (UINT lv = 1; lv <= streamLv; lv++)
		{
			x += dx[i];
			y += dy[i];

			if (x < 0 || x >= MAP_COL || y < 0 || y >= MAP_ROW) break;

			Util::Coord curInvest = { (UINT)x, (UINT)y };

			Block* targetBlock = GM->GetBlockManager()->GetCoordBlock(curInvest);
			
			if (targetBlock) if (targetBlock->IsActive() && !targetBlock->IsHidable()) break;
			
			unsafeCoords.insert(curInvest);
		}
	}

	for (Util::Coord v_c : visited)
		if (Balloon::IsPreDangerZone(v_c) || Stream::IsStreamDangerZone(v_c)) unsafeCoords.insert(v_c);

	return unsafeCoords.size() < visited.size();
}

Util::Coord Enemy::GetIdealDeployCoord(const vector<Util::Coord>& deployables)
{
	static int dx[4] = { 0, 0, -1, 1 };
	static int dy[4] = { 1, -1, 0, 0 };

	vector<Util::Coord> ideals{};

	for (Util::Coord coord : deployables)
	{
		for (UINT i = 0; i < 4; i++)
		{
			int nx = coord.x + dx[i];
			int ny = coord.y + dy[i];

			if (nx < 0 || nx >= MAP_COL || ny < 0 || ny >= MAP_ROW) continue;

			Util::Coord nCoord = { (UINT)nx, (UINT)ny };

			Block* block = GM->GetBlockManager()->GetCoordBlock(nCoord);

			if (block)
			{
				if (block->IsActive() && block->IsBreakable())
					ideals.push_back(coord);
			}
		}
	}
	
	if (!ideals.empty())
	{
		UINT randIdx = Util::GetRandom(0, (int)ideals.size() - 1);
		return ideals[randIdx];
	}

	UINT randIdx = Util::GetRandom(0, (int)deployables.size() - 1);
	return deployables[randIdx];
}

Util::Coord Enemy::GetSafeCoord(const set<Util::Coord>& visited, OUT bool& safeCoordExist)
{
	vector<Util::Coord> safeZones{};

	for (Util::Coord coord : visited)
	{
		if (!Balloon::IsPreDangerZone(coord) && !Stream::IsStreamDangerZone(coord))
			safeZones.push_back(coord);
	}

	if (!safeZones.empty())
	{
		int randIdx = Util::GetRandom(0, (int)safeZones.size() - 1);
		safeCoordExist = true;
		return safeZones[randIdx];
	}
	
	safeCoordExist = false;
	return Util::Coord();
}


void Enemy::Debug()
{
	/*
		PLAYER,
		BALLOON_D_POS,
		AVOID_POS,
		RESCUE_PEER,
		NONE
	*/
	//if (ImGui::BeginMenu("Enemy"))
	//{
	//	ImGui::InputInt("TargetState", (int*)&targetState);
	//	int pathCnt = path.size();
	//	ImGui::InputInt("PathCount", (int*)&pathCnt);
	//	ImGui::EndMenu();
	//}
	
	Character::Debug();
}

