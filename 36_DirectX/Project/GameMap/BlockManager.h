#pragma once

class BlockManager
{
public:
	BlockManager();
	~BlockManager();

	void Update();
	void Render();

private:
	void CreateBlock(Util::Coord coord, wstring file,
					 Util::Coord frameXY = { 1, 1 },
					 Util::Coord targetXY = {1, 1},
					 Vector2 texWorldSize = CELL_WORLD_SIZE,
					 BlockProperty bProp = {});

private:
	
	Block* blocks[MAP_ROW][MAP_COL]{};
	
	Animation* destroyedAnim{};
};
