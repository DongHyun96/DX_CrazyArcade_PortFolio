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

};
