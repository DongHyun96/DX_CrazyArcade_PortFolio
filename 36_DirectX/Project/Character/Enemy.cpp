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
		// 0.5초에 한 번 2초 뒤 한번 더 호출해주어 한번 더 도움 요청함
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


	if (dir.Length() < 1.f)// destination reached로 판단 -> 여기서 경로 재설정 트리거가 동작해야함 & path가 비었을 때도 한번 동작해야 함
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

		if (blockedTime >= BLOCKED_TIME_LIMIT) // Path가 아직 남아있고 한자리에 계속 머물 때 어디에 막혔을것이라 판단 -> 다시 None으로 돌아가서 재판단
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
	// path가 empty이면 도착했다는 얘기

	//TargetState prevState = targetState;
	//if (path.empty()) targetState = NONE;

	switch (targetState)
	{
	case Enemy::PLAYER:
		if (path.size() <= player_approach_lv) // 랜덤하게 지정한 approach_lv에 도달했다면 경로에 도달했다고 판단
		{
			DeployBalloonManually();
			targetState = NONE;
		}
		break;
	case Enemy::BALLOON_D_POS: // 물풍선을 놓은 뒤 가장 가까운 safe_zone으로 가야함
		if (path.empty())
		{
			DeployBalloonManually();
			targetState = SAFE_ZONE;

			// 플레이어 위치로 path Update 시도
			Util::Coord pCurCoord = GM->GetCollidedMapCellCoord(PM->GetP1()->GetBody()->GlobalPosition());
			UpdatePath(pCurCoord);
			
			if (!path.empty())
			{
				// 확률상으로 플레이어에게 접근할지 말지 계산 X 이거 하지 말고 새로운 위험반경 조사해서 새로운 safezone으로 이동하는게 나을수도 있음
			}
			else
			{
				// 아직 섬 -> 바로 가장 가까운 safezone으로 이동
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
			
			if (Balloon::IsPreDangerZone(myCoord)) // 현재 자신의 위치가 곧 있으면 위험한 자리면 다른 자리로 이동
			{
				safeZoneWaitTime = 0.f;
				targetState = NONE;
			}

			if (safeZoneWaitTime < SAFE_ZONE_WAIT_TIME) return; // safe_zone에서 3초간 대기한 뒤 다시금 길찾기

			safeZoneWaitTime = 0.f;
			targetState = NONE;
		}
		break;
	case Enemy::RESCUE_PEER:
		
		if (rescueTarget->GetCharacterState() != C_CAPTURED || path.empty()) // 이미 구해졌거나 이미 죽은 상태
		{
			path = {};
			visited.clear();
			targetState = NONE;
		}
		break;
	case Enemy::NONE: // None일 때에는 바로 상태 변환 시도
	{
		// 플레이어의 approximate 위치로 path Update 시도
		Util::Coord approximate_player_coord = PM->GetApproximatedPlayerCoord(PM->GetP1());
		UpdatePath(approximate_player_coord);

		if (path.empty()) // 플레이어까지의 도달경로가 없을 때
		{
			// 물풍선을 놓을 위치 판단
			vector<Util::Coord> deployable = GetDeployableCoords(visited);

			// 물풍선을 놓을 자리가 없다면 처음으로 돌아감
			if (deployable.empty()) break; 

			// 물풍선을 놓을 자리 중 이상적인 자리로 설정
			Util::Coord targetCoord = GetIdealDeployCoord(deployable);
			
			// 물풍선을 놓을자리로 경로 설정
			UpdatePath(targetCoord);
			
			targetState = BALLOON_D_POS;
		}
		else if (path.size() > 10) // 플레이어까지의 도달경로가 존재는 하지만 너무 멀 때
		{
			targetState = PLAYER;
		}
		else // 플레이어 위치까지 가기
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

	if (!timerBalloons.empty()) // 타이머 벌룬이 세팅되어있을 때
	{

		// 타이머 벌룬을 한번에 터침
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

void Enemy::RequestRescue() // 처음 한번 호출하고 몇초 뒤 한번 더 호출해봄 (총 두번)
{
	/* 동료들을 거리순으로 정렬 */
	set<pair<UINT, Character*>> sortedByDist{};

	for (Character* target : GM->GetPlayerManager()->GetComEnemies())
	{
		Util::Coord targetCoord = GM->GetCollidedMapCellCoord(target->GetBody()->GlobalPosition());
		UINT dist = Util::GetDist(myCoord, targetCoord);

		sortedByDist.insert(make_pair(dist, target));
	}

	for (const auto& p : sortedByDist) // 가장 가까운 거리에 존재하는 동료 순
	{
		Character* target = p.second;

		// 현재 동료가 도와줄 수 없는 상황이면 넘어감
		if (target->GetCharacterState() == C_CAPTURED || target->GetCharacterState() == C_DEAD)
			continue;

		// 현재 동료까지의 경로가 존재하는지 체크, targetCoord -> 현재 동료의 위치
		Util::Coord targetCoord = GM->GetCollidedMapCellCoord(target->GetBody()->GlobalPosition());

		// Captured당한 나 자신으로부터 동료까지의 경로가 존재하는지 체크함 (내 path를 Update해봄)
		UpdatePath(targetCoord);

		// 해당하는 경로가 없다면 다음 동료로 다시 시도
		if (path.empty()) continue;

		// for loop의 현재 동료가 경로가 존재하는 가장 가까운 동료 -> 내가 찾은 경로를 백트래킹하여 구조를 요청할 동료의 path에 넣어줌
		stack<Util::Coord> rescuerPath{}; // 구조자 경로
		
		// 내가 찾은 경로를 역으로 넣어주되, 구조자 경로의 끝에는 나의 좌표를 넣어주고, 경로의 시작(rescuer자기자신의 현위치) 부분은 하나 빼줘야 함

		rescuerPath.push(myCoord);

		while (!path.empty())
		{
			rescuerPath.push(path.top());
			path.pop();
		}

		rescuerPath.pop();

		// 동료의 targetState를 RESCUE_PEER로 바꾸고 path도 나 자신을 구하러 오는 path로 수정
		Enemy* peer = dynamic_cast<Enemy*>(target);
		peer->SetPathToRescueMission(make_pair(rescuerPath, visited), this);

		// 구조요청 후 나 자신의 path, visited, targetState 초기화
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

	// 안전하지 못한 좌표들을 조사할 것임
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

