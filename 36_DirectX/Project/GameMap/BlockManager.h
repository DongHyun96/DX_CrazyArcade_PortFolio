#pragma once

class BlockManager
{
public:
	BlockManager();
	~BlockManager();

	void Update();
	void Render();

public:
	/// <summary>
	/// ��ϳ����� ��ġ ���� �ٲٱ�
	/// </summary>
	/// <param name="c1"> : First block cell pos  </param>
	/// <param name="c2"> : Second block cell pos </param>
	static void SwapBlocks(const Util::Coord& c1, const Util::Coord& c2);

public:
	/* dest ��ġ�� ����� �̵����ѵ� ������ �ڸ����� üũ */
	static bool IsValidDestCoord(const Util::Coord& dest);

public:
	/* �ش� ��ġ�� Block Getter */
	static Block* GetCoordBlock(const Util::Coord& coord) { return blocks[coord.y][coord.x]; }

private: /* BlockManager���� Block ���� ���� */

	/// <param name="coord"> : ����� ���� cell coord </param>
	/// <param name="file"> : ��� Texure file </param>
	/// <param name="frameXY"> : Texture file�� Row, col ������ �� ���� </param>
	/// <param name="targetXY"> : Texture file ������ ����� ������ ��ġ </param>
	/// <param name="texWorldSize"> : World�� ��ġ�� size ���� </param>
	/// <param name="bProp"> : ����� Ư�� </param>
	/// <returns> ������ ��� ��ü </returns>
	Block* CreateBlock(Util::Coord coord, wstring file,
					   Util::Coord frameXY = { 1, 1 },
					   Util::Coord targetXY = {1, 1},
					   Vector2 texWorldSize = CELL_WORLD_SIZE,
					   BlockProperty bProp = {});

	/// <summary>
	/// ���ο� BlockManager ���� ��, �ʿ� �´� Block�� Load�ϸ鼭 Block�� ������ �� ���
	/// </summary>
	/// <param name="info"> : Load�� BlockInfo</param>
	/// <param name="boardXY"> : ���� ������ cell pos </param>
	/// <returns> ������ ��� ��ü</returns>
	Block* CreateBlock(const BlockInfo& info, Util::Coord boardXY); // ���� �� Load�� �� create�ϴ� �뵵

private:
	 /* 
	 GameManager���� curMapType(���� ���õ� ���Ӹ�)�� ���� ��ϵ� ���� �ε�
	 ���� GameMap�� �� cell�� ���� block info�� �ҷ����� �ش� cell�� ��� ������ block�� �ʱ�ȭ ���
	 */
	void Load();

private: /* Collision Handling ���� */
	
	void HandleCommonCollisions();						// �⺻���� CommonCollision handling
	void HandleCharacterCommonCollision(Block* block);  // HandleCommonCollisions���� call
	void HandleDartCollision(Block* block);				// HandleCommonCollisions���� call

	void HandleMovableCollisions();						// Movable vs Character  collision handling
	void HandleHidableCollisions();						// Hidable vs (Movable, Balloon) collision handling


private:

	/* Total block fields */
	static Block*	blocks[MAP_ROW][MAP_COL]; 
	
	vector<Block*>	movableBlocks{};
	vector<Block*>	hidableBlocks{};

	/* Each cells block infos */
	BlockInfo		infos[MAP_ROW][MAP_COL]{};
};
