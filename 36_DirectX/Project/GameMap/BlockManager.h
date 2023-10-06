#pragma once

class BlockManager
{
public:
	BlockManager();
	~BlockManager();

	void Update();
	void Render();

	static void SwapBlocks(const Util::Coord& c1, const Util::Coord& c2);

	// �����̰��� �ϴ� ��ġ�� valid���� üũ
	static bool IsValidDestCoord(const Util::Coord& dest);

private:
	Block* CreateBlock(Util::Coord coord, wstring file,
					 Util::Coord frameXY = { 1, 1 },
					 Util::Coord targetXY = {1, 1},
					 Vector2 texWorldSize = CELL_WORLD_SIZE,
					 BlockProperty bProp = {});

	Block* CreateBlock(const BlockInfo& info, Util::Coord boardXY); // ���� �� Load�� �� create�ϴ� �뵵

	void Load();

private:
	
	void HandleCharacterBlockCollision();   // Common collision
	void HandleMovableCollisions();
	void HandleHidableCollisions();

	

private:

	static Block* blocks[MAP_ROW][MAP_COL]; // Total block fields
	
	vector<Block*> movableBlocks{};
	vector<Block*> hidableBlocks{};

	BlockInfo infos[MAP_ROW][MAP_COL]{};

	Animation* destroyedAnim{};
};
