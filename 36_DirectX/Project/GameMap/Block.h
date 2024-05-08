#pragma once

#define BLOCK_Y_OFFSET 10.f // 블록을 깔 때, CELL의 정중앙 위치에 까는 것이 아닌 위쪽으로 Offset만큼 올릴 것임

class Character;
class Player;
class Item;


/* 블록의 특성 구조체 */
struct BlockProperty
{
	bool breakable{};
	bool movable{};
	bool hidable{};
};

/* Block에 대해 save & load할 정보들 */
struct BlockInfo
{
	BlockInfo() {}

	/// <param name="file"> : Texture file path </param>
	/// <param name="boardXY"> : 게임 보드 내의 좌표 </param>
	/// <param name="frameXY"> : Texture 파일의 Row, col 프레임 총 개수 </param>
	/// <param name="targetXY"> : Texture 파일 내에서 사용할 프레임 위치 </param>
	/// <param name="bProp"> : 블록의 특성 </param>
	/// <param name="texWorldSize"> : World에 배치될 size 지정 </param>
	BlockInfo
	(
		wstring file, 
		Util::Coord boardXY,
		Util::Coord frameXY, Util::Coord targetXY,
		BlockProperty bProp,
		Vector2 texWorldSize = CELL_WORLD_SIZE
	)
		:file(file), boardXY(boardXY), frameXY(frameXY), targetXY(targetXY), bProp(bProp), texWorldSize(texWorldSize)
	{ initialized = true; }

	/// <summary>
	/// BlockInfo bin 파일 내용으로 저장
	/// </summary>
	/// <param name="binWriter"> : BinaryWriter reference </param>
	void SaveData(BinaryWriter& binWriter)
	{
		binWriter.WriteData(initialized);
		binWriter.WriteData(file);
		binWriter.WriteData(boardXY);
		binWriter.WriteData(frameXY);
		binWriter.WriteData(targetXY);
		binWriter.WriteData(bProp.breakable);
		binWriter.WriteData(bProp.movable);
		binWriter.WriteData(bProp.hidable);
		binWriter.WriteData(texWorldSize);
	}

	/// <summary>
	/// Bin파일 저장 내용 불러오기
	/// </summary>
	/// <param name="binReader"> : BinaryReader reference </param>
	void ReadAndCopy(BinaryReader& binReader)
	{
		initialized			= binReader.ReadInt();

		binReader.ReadAndCopyWstr(file);

		boardXY				= binReader.ReadCoord();
		frameXY				= binReader.ReadCoord();
		targetXY			= binReader.ReadCoord();
		bProp.breakable		= binReader.ReadInt();
		bProp.movable		= binReader.ReadInt();
		bProp.hidable		= binReader.ReadInt();
		texWorldSize		= binReader.ReadVector2();
	}

	bool initialized{}; // 초기화 여부 확인용

	wstring			file{};								// Texture file path
	Util::Coord		boardXY{};							// 게임 보드 좌표 (Cell 좌표)
	Util::Coord		frameXY{};							// Texture 파일의 Row, col 프레임 총 개수
	Util::Coord		targetXY{};							// Texture 파일 내에서 사용할 프레임 위치
	BlockProperty	bProp{};							// 블록의 특성
	Vector2			texWorldSize{ CELL_WORLD_SIZE };	// World에 배치될 size 지정
};

/*
CONCRETE CLASS
*/
class Block : public ColliderHolder
{
public:

	Block(const BlockInfo& info);

	// texWorldSize에 디폴트로 y offset을 조금 두어 머리부분이 뒤로 조금 넘어가게끔 미세하게 조정할 것임
	Block
	(
		Util::Coord boardXY, wstring texFile, 
		Util::Coord frameXY  = {1, 1},
		Util::Coord targetXY = {1, 1},
		Vector2 texWorldSize = CELL_WORLD_SIZE,
		BlockProperty bProp = {}
	);

	~Block();

	void Update();
	void Render();

private:

	/// <summary>
	/// block 이동 시도
	/// </summary>
	/// <param name="destBoardCoordX"> : 이동할 destination board coord X 좌표 </param>
	/// <param name="destBoardCoordY"> : 이동할 destination board coord Y 좌표 </param>
	/// <returns> 이동 성공 여부 </returns>
	bool Move(const UINT& destBoardCoordX, const UINT& destBoardCoordY);

	/// <summary>
	/// block 이동 시도
	/// </summary>
	/// <param name="destCoord"> : 이동할 destination board coord </param>
	/// <returns> 이동 성공 여부 </returns>
	bool Move(const Util::Coord& destCoord);

	/// <summary>
	/// block 이동 시도
	/// </summary>
	/// <param name="destination"> : 이동할 실제 Vector2 좌표 </param>
	/// <returns> 이동 성공 여부 </returns>
	bool Move(Vector2 destination);

	/* block 이동 시 이동처리 담당 (Called in Update) */
	void HandleMove();

public:
	/* Applying damage to this block */
	void ApplyDamage();

public: /* Getters, setters */

	ColliderRect*	GetBody()								{ return rectBody; }
	Vector2			GetTranslation() const					{ return rectBody->translation; }
	
	void			SetBoardPos(const Util::Coord& coord)	{ this->boardPos = coord; }
	Util::Coord		GetBoardPos() const						{ return boardPos; }

	bool			IsActive() const						{ return isActive; }
	void			SetActive(const bool& active)			{ this->isActive = active; }
	void			SetVisible(const bool& visible)			{ this->visible = visible; }

	bool			IsMovable() const						{ return movable; }
	bool			IsBreakable() const						{ return breakable; }
	bool			IsHidable() const						{ return hidable; }

	void			SetLabel(const string& label)			{ this->label = label; }

private:
	/* 수풀 interaction 실시 */
	void PlayBushInteraction();

	/* currentlyBushing을 체크하여 수풀 interaction handling */
	void HandleBushInteraction();
	
private: /* Collider call back functions */

	void OnColliderPointEnter(ColliderHolder* owner);
	void OnColliderPointStay(ColliderHolder* owner);
	void OnColliderPointExit(ColliderHolder* owner);

	void OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner);
	void OnColliderRectStay(ColliderRect* targetCollider, ColliderHolder* owner);
	void OnColliderRectExit(ColliderRect* targetCollider, ColliderHolder* owner);

private:

	/// <param name="cDirection"> : 현재 캐릭터가 향하는 방향 </param>
	/// <param name="collidedFace"> : 현재 캐릭터와 충돌중인 block의 면 방향 </param>
	/// <returns></returns>
	bool IsPushing(const Direction& cDirection, const Direction& collidedFace);

private:
	/* 랜덤한 확률로 아이템 생성 시도 */
	void HandleAddItem();

public: /* Debugging */

	void Debug();
	void Debug(const string& label);

private:

	ColliderRect*	rectBody{}; // body collider
	Object*			texObj{};	// Texture rendering object

private:

	bool isActive = true;
	bool visible  = true;
	bool destroyed{};

private: /* Block properties */

	bool breakable{};
	bool movable{};
	bool hidable{};

private:

	UINT		hp{1};				// 블록의 체력
	Animation*	destroyedAnim{};	// 블록이 부서질 때 재생할 animation

private: /* Movable block 관련 */

	Util::Coord boardPos{};							// 보드 Cell 좌표
	Vector2		destination{};						// 이동할 위치
	bool		currentlyMoving{};					// 현재 움직이는 중인지
	float		pushForceAppliedTime{};				// 밀림 당한 시간 체크 timer
	const float PUSH_APPLIED_TIME_LIMIT{ 0.2f };	// 밀릴 시간 threshold

private: /* 수풀 block Interaction 관련 */

	bool	currentlyBushing{};		// 수풀 interaction이 진행중인지 (ex - bush animation, bush sound play)
	float	bushInteractedTime{};	// 수풀 interaction이 진행한 총 시간

private: /* 아이템 관련(가지고 있을 수도 없을 수도 있음) */
	
	/* 
	Block에서 랜덤하게 생성 -> 생성되었다면 해당 아이템을 ItemManager에 넘겨서 ItemManager에서 일괄적으로 managing
	아이템 매니저에서 일괄 삭제, Update, Render할 예정
	*/
	Item* item{};

private:
	string label{}; // Debug label

};
