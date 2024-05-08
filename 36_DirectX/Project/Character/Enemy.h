#pragma once
/* 
CONCRETE CLASS
자체 decision-making process에 의해 control될 enemy 캐릭터
*/
class Enemy : public Character
{

public:
	Enemy(const CharacterType& cType);
	~Enemy();

public:
	
	/// <summary>
	/// 구조할 경로와 구조대상을 세팅
	/// </summary>
	/// <param name="rescue_path_visited_pair"> : 구조경로와 AStar 알고리즘 visited pair</param>
	/// <param name="rescueTarget"> : 구조할 동료</param>
	void SetPathToRescueMission(const pair<stack<Util::Coord>, set<Util::Coord>>& rescue_path_visited_pair, Character* rescueTarget);

private:

	void Move()						override;
	void HandleUseConsumableItem()	override;
	void DeployBalloon()			override; 
	
	void Init()						override;

private:
	/* targetState에 따른 FSM 상황조치 */
	void UpdateState();

private:
	/* 새로운 목표지점으로 path 갱신 */
	void UpdatePath(const Util::Coord& dest);

private:
	/* 다른 동료에게 구조요청 시도 */
	void RequestRescue(); 

private: /* 물풍선 놓기 관련 */
	
	/* 물풍선 놓기 */
	void DeployBalloonManually();
	
	/// <summary>
	/// AStar로 방문한 좌표 중 물풍선을 놓아도 안전지대가 확보되는 좌표들 찾기
	/// </summary>
	/// <param name="visited"> : AStar로 방문한 좌표</param>
	/// <returns>안전지대가 확보되는 좌표들</returns>
	vector<Util::Coord> GetDeployableCoords(const set<Util::Coord>& visited);

	/// <summary>
	/// 해당 좌표에 물풍선을 놓아도 안전지대가 확보가 되는지 검사
	/// </summary>
	/// <param name="coord"> : 검사할 좌표</param>
	/// <param name="visited"> : AStar로 방문처리된 좌표들</param>
	/// <returns></returns>
	bool IsDeployable(const Util::Coord& coord, const set<Util::Coord>& visited);

	/// <summary>
	/// 물풍선을 놓을 수 있는 좌표들 중 좀 더 이상적인 좌표(ex - 부서지는 블록 옆)를 구하는 함수
	/// </summary>
	/// <param name="deployables"> : 물풍선을 놓을 수 있는 좌표들</param>
	/// <returns>물풍선을 놓을 이상적인 좌표</returns>
	Util::Coord GetIdealDeployCoord(const vector<Util::Coord>& deployables); 
	
private:
	/// <summary>
	/// 안전할 이동 좌표 구하기
	/// </summary>
	/// <param name="visited"> : AStar로 방문처리된 좌표들</param>
	/// <param name="safeCoordExist"> : 안전할 이동좌표가 있는지에 대한 OUT reference 결과</param>
	/// <returns>안전할 이동좌표</returns>
	Util::Coord GetSafeCoord(const set<Util::Coord>& visited, OUT bool& safeCoordExist);

private:
	void Debug() override;



/***************************************************************************************************
*                                          Member variables                                        *
****************************************************************************************************/
private:

	/* Enemy target state - 현재 이동할 목표 target 종류 */
	enum TargetState
	{
		PLAYER,
		BALLOON_D_POS,		// 물풍선을 놓을 자리로 이동
		SAFE_ZONE,			// 물줄기에 닿지 않을 자리로 이동
		RESCUE_PEER,		// 구조요청을 다른 동료에게서 받으면, 물풍선에 갇힌 동료 위치로 이동
		NONE				// 목표 target이 잡히지 않은 상태
	} targetState = NONE;

private:
	/* 게임맵에서의 현재 좌표 */
	Util::Coord myCoord{};

private: /* 이동 경로 관련 */

	stack<Util::Coord>	path{};		// AStarPathFinder를 통한 목표지점까지의 경로
	set<Util::Coord>	visited{};	// AStarPathFinder를 통해 AStar 알고리즘 상 방문했던 좌표들

private: /* Safe zone에 도착 시 기다릴 time */

	const float SAFE_ZONE_WAIT_TIME = 3.f;	// Safe Zone 도착 시, 위협이 없다면 해당 자리에서 대기할 시간
	float		safeZoneWaitTime{};

private: /* 경로 이동 중 경로가 막혔을 때 관련 */
	// 경로 이동 중 특정 시간 이상 같은 자리에 머무른다면, 경로가 방해받았다고 판단하여 targetState를 NONE으로 두어 경로 재탐색

	const float BLOCKED_TIME_LIMIT = 0.5f;
	float		blockedTime{};

private: /* 이동 목표지점이 player 위치일 때, 목표지점 조정 관련 */
	// 플레이어에게 이동 목표로 설정 시, 완전히 접근하는 것이 아닌 랜덤하게 거리차를 조정할 것임

	const UINT	PLAYER_APPROACH_MIN = 0;	// 최소 접근 거리차
	const UINT	PLAYER_APPROACH_MAX = 3;	// 최대 접근 거리차
	UINT		player_approach_lv{};		// 랜덤하게 setting한 player 목표 지점까지의 거리차

private: /* RESCUE 관련(내가 구조할 때) */

	Character* rescueTarget{}; // 구조해야 할 동료

private: /* RESCUE 관련(내가 물풍선에 갇혀서 다른 동료의 도움을 받아야 할 때) */

	bool		requestResqueOnce{};			// 첫 구조신호를 보냈는지 체크
	bool		requestResqueTwice{};			// 두번 째 구조신호를 보냈는지 체크

	const float RESCUE_CALL_TIME_ONCE  = 0.5f;	// 해당 시간이 흐른 후, 첫 구조요청 진행
	const float RESCUE_CALL_TIME_TWICE = 2.f;	// 해당 시간이 흐른 후, 두 번째 구조요청 진행
	float		capturedTime		   = 0.f;	// 물풍선에 갇힌 총 시간


};
