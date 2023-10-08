#pragma once
class Stream
{
public:
	Stream();
	~Stream();

	void Update();
	void Render();

	void Spawn(const Util::Coord& spawnCoord, const UINT& streamLv);

	bool IsActive() const { return isActive; }

private:

	void InitReachedMap(const Util::Coord& spawnCoord, const UINT& streamLv);

	void HandleSpawning();

	// 모두 다 꺼지면 자신의 active도 끔
	void HandleActive();

private:

	bool isActive{};

	StreamBlock* centerStream{};

	static const UINT DIR_STREAM_CNT{ 80 };

	map<Direction, vector<StreamBlock*>> dirStreamMap{};
	map<Direction, deque<Util::Coord>> reachedCoordMap{};

private:
	
	const float BLOCK_SPAWN_DELTA{ 0.1f };

	float blockSpawnTime = 0.f;
	UINT curSpawnIdx{};
	bool stopSpawning{true};

};
