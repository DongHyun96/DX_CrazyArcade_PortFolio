#pragma once

class BlockManager
{
public:
	BlockManager();
	~BlockManager();

	void Update();
	void Render();

	void CreateBlock(Util::Coord coord, wstring file,
					 Util::Coord frameXY = { 1, 1 },
					 Util::Coord targetXY = {1, 1},
					 Vector2 texWorldSize = CELL_WORLD_SIZE,
					 BlockProperty bProp = {});

private:
	//vector<Block*> blocks{};
	vector<Block*> blocks{};

	Animation* destroyedAnim{};
};
