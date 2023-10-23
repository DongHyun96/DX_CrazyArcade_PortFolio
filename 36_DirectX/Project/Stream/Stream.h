#pragma once
class Stream
{
public:
	Stream(StreamBlockManager* streamBlockManager);
	~Stream();

	void Init();

	void Update();

	void Spawn(const Util::Coord& spawnCoord, const UINT& streamLv);

	bool IsActive() const { return isActive; }

	static void AddStreamDanagerZone(const Util::Coord& balloonCoord, const UINT& streamLv);// Balloon 스폰 시 insert
	static void EraseStreamDangerZone(const Util::Coord& coord) { streamDangerZone.erase(coord); }
	static bool IsStreamDangerZone(const Util::Coord& coord) { return (streamDangerZone.find(coord) != streamDangerZone.end()); }

private:

	void InitReachedMap(const Util::Coord& spawnCoord, const UINT& streamLv);

	void HandleChainExplosion();

	void HandleSpawning();

	// 모두 다 꺼지면 자신의 active도 끔
	void HandleSelfActive();

private:

	bool isActive{};

	StreamBlockManager* streamBlockManager; // StreamManager에서 받아옴

	map<Direction, deque<Util::Coord>> reachedCoordMap{};

private:
	
	const float BLOCK_SPAWN_DELTA{ 0.05f };

	float blockSpawnTime = 0.f;
	bool stopSpawning{true};

private:
	vector<StreamBlock*> activatedBlocks{};
	
	//실제 stream 위치를 저장 -> AStar에서 cell 판단 시 사용
	static set<Util::Coord> streamDangerZone;

};
