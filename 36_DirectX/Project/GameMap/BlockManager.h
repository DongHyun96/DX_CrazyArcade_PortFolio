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
	/// 블록끼리의 위치 서로 바꾸기
	/// </summary>
	/// <param name="c1"> : First block cell pos  </param>
	/// <param name="c2"> : Second block cell pos </param>
	static void SwapBlocks(const Util::Coord& c1, const Util::Coord& c2);

public:
	/* dest 위치에 블록을 이동시켜도 가능한 자리인지 체크 */
	static bool IsValidDestCoord(const Util::Coord& dest);

public:
	/* 해당 위치의 Block Getter */
	static Block* GetCoordBlock(const Util::Coord& coord) { return blocks[coord.y][coord.x]; }

private: /* BlockManager내의 Block 생성 관련 */

	/// <param name="coord"> : 블록을 만들 cell coord </param>
	/// <param name="file"> : 블록 Texure file </param>
	/// <param name="frameXY"> : Texture file의 Row, col 프레임 총 개수 </param>
	/// <param name="targetXY"> : Texture file 내에서 사용할 프레임 위치 </param>
	/// <param name="texWorldSize"> : World에 배치될 size 지정 </param>
	/// <param name="bProp"> : 블록의 특성 </param>
	/// <returns> 생성한 블록 객체 </returns>
	Block* CreateBlock(Util::Coord coord, wstring file,
					   Util::Coord frameXY = { 1, 1 },
					   Util::Coord targetXY = {1, 1},
					   Vector2 texWorldSize = CELL_WORLD_SIZE,
					   BlockProperty bProp = {});

	/// <summary>
	/// 새로운 BlockManager 생성 시, 맵에 맞는 Block을 Load하면서 Block을 생성할 때 사용
	/// </summary>
	/// <param name="info"> : Load된 BlockInfo</param>
	/// <param name="boardXY"> : 게임 보드의 cell pos </param>
	/// <returns> 생성한 블록 객체</returns>
	Block* CreateBlock(const BlockInfo& info, Util::Coord boardXY); // 시작 시 Load할 때 create하는 용도

private:
	 /* 
	 GameManager에서 curMapType(현재 선택된 게임맵)에 따른 블록들 정보 로딩
	 현재 GameMap의 각 cell에 대한 block info를 불러오고 해당 cell의 블록 정보로 block들 초기화 담당
	 */
	void Load();

private: /* Collision Handling 관련 */
	
	void HandleCommonCollisions();						// 기본적인 CommonCollision handling
	void HandleCharacterCommonCollision(Block* block);  // HandleCommonCollisions에서 call
	void HandleDartCollision(Block* block);				// HandleCommonCollisions에서 call

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
