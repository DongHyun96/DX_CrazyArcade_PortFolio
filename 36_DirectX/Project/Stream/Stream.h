#pragma once
/* 
CONCRETE CLASS
스폰 위치(가운데 StreamBlock의 위치)와 물줄기 level을 받아,
시간차를 두어 가운데 StreamBlock부터 일정한 시간간격으로 4방향 StreamBlock 스폰 처리 담당
*/
class Stream
{
public:
	Stream();
	~Stream();

	void Init();

	void Update();

public:

	/// <summary>
	/// <para> spawnCoord(가운데 streamBlock위치)부터 시작해서 streamLv에 따라(그리고 지형지물에 따라) </para>
	/// <para> StreamBlock을 시간차를 두고 스폰 </para>
	/// </summary>
	/// <param name="spawnCoord"> : 물줄기 스폰 정가운데 위치 </param>
	/// <param name="streamLv"> : 물줄기 level </param>
	void Spawn(const Util::Coord& spawnCoord, const UINT& streamLv);

public:

	bool IsActive() const { return isActive; }

public: /* StreamDanagerZone 관련 (Enemy와 PathFinding에서 필요) */

	/// <summary>
	/// Balloon이 터질 때, 터진 balloon의 좌표와 streamLv를 받아 물줄기 위험 지역 추가
	/// </summary>
	/// <param name="balloonCoord"> : 터진 balloon의 좌표 </param>
	/// <param name="streamLv"> : Stream level </param>
	static void AddStreamDanagerZone(const Util::Coord& balloonCoord, const UINT& streamLv);
	
	static void EraseStreamDangerZone(const Util::Coord& coord) { streamDangerZone.erase(coord); }

	static bool IsStreamDangerZone(const Util::Coord& coord) { return (streamDangerZone.find(coord) != streamDangerZone.end()); }

private:
	/// <summary>
	/// 첫 spawn시 어느지점까지 도달하는지 reachedCoordMap 초기화
	/// </summary>
	/// <param name="spawnCoord"> : Spawn 위치(가운데 StreamBlock위치) </param>
	/// <param name="streamLv"> : Stream level </param>
	void InitReachedMap(const Util::Coord& spawnCoord, const UINT& streamLv);

	/* 물줄기 도달 지점 범위 내에 balloon이 있는지 조사해서 있다면 해당 balloon들 모두 연쇄 폭발 시킴 */
	void HandleChainExplosion();

	/* 시간차를 두고 각 방향의 StreamBlock들을 spawn시킴 */
	void HandleSpawning();

	/* this가 스폰시킨 StreamBlock이 모두 다 꺼지면 자신의 active도 끔 */
	void HandleSelfActive();

/***************************************************************************************************
*                                          Member variables                                        *
****************************************************************************************************/

private:

	bool isActive{};

private:
	/* 각 Direction 별로 도달한 모든 좌표들 */
	map<Direction, deque<Util::Coord>> reachedCoordMap{};

private:
	/* 가장 최근 spawn된 물줄기 block과 그 다음 spawn될 물줄기 block의 spawn 시간차 */
	const float BLOCK_SPAWN_DELTA{ 0.05f };

	float		blockSpawnTime = 0.f;
	bool		stopSpawning = true;

private:
	/* 이 Stream(this) 객체가 스폰시킨 activated streamBlocks */
	vector<StreamBlock*> activatedBlocks{};
	
	//실제 stream 위치를 저장 -> AStar에서 cell 판단 시 사용
	static set<Util::Coord> streamDangerZone;

};
