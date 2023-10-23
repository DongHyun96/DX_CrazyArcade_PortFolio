#pragma once
class StreamManager
{
public:
	StreamManager();
	~StreamManager();

	void Update();
	void Render();

	void SpawnStream(const Util::Coord& spawnCoord, const UINT& streamLv);

	void Init();

private:


private:
	
	const UINT POOL_CNT{ 60 };

	vector<Stream*> streams{};

	StreamBlockManager* streamBlockManager{};

};
