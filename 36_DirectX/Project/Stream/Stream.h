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

	static void AddStreamDanagerZone(const Util::Coord& balloonCoord, const UINT& streamLv);// Balloon ���� �� insert
	static void EraseStreamDangerZone(const Util::Coord& coord) { streamDangerZone.erase(coord); }
	static bool IsStreamDangerZone(const Util::Coord& coord) { return (streamDangerZone.find(coord) != streamDangerZone.end()); }

private:

	void InitReachedMap(const Util::Coord& spawnCoord, const UINT& streamLv);

	void HandleChainExplosion();

	void HandleSpawning();

	// ��� �� ������ �ڽ��� active�� ��
	void HandleSelfActive();

private:

	bool isActive{};

	StreamBlockManager* streamBlockManager; // StreamManager���� �޾ƿ�

	map<Direction, deque<Util::Coord>> reachedCoordMap{};

private:
	
	const float BLOCK_SPAWN_DELTA{ 0.05f };

	float blockSpawnTime = 0.f;
	bool stopSpawning{true};

private:
	vector<StreamBlock*> activatedBlocks{};
	
	//���� stream ��ġ�� ���� -> AStar���� cell �Ǵ� �� ���
	static set<Util::Coord> streamDangerZone;

};
