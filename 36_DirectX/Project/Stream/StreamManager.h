#pragma once
class StreamManager
{
public:
	StreamManager();
	~StreamManager();

	void Update();
	void Render();

	void SpawnStream(const Util::Coord& spawnCoord, const UINT& streamLv);

private:
	
	const UINT POOL_CNT{ 80 };

	vector<Stream*> streams{};

	StreamBlockManager* streamBlockManager{};


};
