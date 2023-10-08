#pragma once
class StreamBlockManager
{
public:
	StreamBlockManager();
	~StreamBlockManager();

	void Update();
	void Render();
	
	StreamBlock* GetAvailableBlock(const Direction& dir);

	StreamBlock* Spawn(const Direction& dir, const Util::Coord& spawnCoord, const bool& isEnd = false);


private:

	/*const UINT CENTER_POOL_CNT = 80;
	const UINT DIR_POOL_CNT = 64;*/

	const UINT CENTER_POOL_CNT = 80;
	const UINT DIR_POOL_CNT = 64;

	vector<StreamBlock*> centerBlocks{};
	map<Direction, vector<StreamBlock*>> dirStreamMap{};

	
};
