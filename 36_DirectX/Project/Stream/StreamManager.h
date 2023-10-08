#pragma once
class StreamManager
{
public:
	StreamManager();
	~StreamManager();

	void Update();
	void Render();

	void Spawn(const Util::Coord& spawnCoord, const UINT& streamLv);

private:

	const UINT POOL_CNT{ 30 };

	vector<Stream*> streams{};

};
