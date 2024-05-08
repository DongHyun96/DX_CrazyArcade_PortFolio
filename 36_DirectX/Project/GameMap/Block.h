#pragma once

#define BLOCK_Y_OFFSET 10.f // ����� �� ��, CELL�� ���߾� ��ġ�� ��� ���� �ƴ� �������� Offset��ŭ �ø� ����

class Character;
class Player;
class Item;


/* ����� Ư�� ����ü */
struct BlockProperty
{
	bool breakable{};
	bool movable{};
	bool hidable{};
};

/* Block�� ���� save & load�� ������ */
struct BlockInfo
{
	BlockInfo() {}

	/// <param name="file"> : Texture file path </param>
	/// <param name="boardXY"> : ���� ���� ���� ��ǥ </param>
	/// <param name="frameXY"> : Texture ������ Row, col ������ �� ���� </param>
	/// <param name="targetXY"> : Texture ���� ������ ����� ������ ��ġ </param>
	/// <param name="bProp"> : ����� Ư�� </param>
	/// <param name="texWorldSize"> : World�� ��ġ�� size ���� </param>
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
	/// BlockInfo bin ���� �������� ����
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
	/// Bin���� ���� ���� �ҷ�����
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

	bool initialized{}; // �ʱ�ȭ ���� Ȯ�ο�

	wstring			file{};								// Texture file path
	Util::Coord		boardXY{};							// ���� ���� ��ǥ (Cell ��ǥ)
	Util::Coord		frameXY{};							// Texture ������ Row, col ������ �� ����
	Util::Coord		targetXY{};							// Texture ���� ������ ����� ������ ��ġ
	BlockProperty	bProp{};							// ����� Ư��
	Vector2			texWorldSize{ CELL_WORLD_SIZE };	// World�� ��ġ�� size ����
};

/*
CONCRETE CLASS
*/
class Block : public ColliderHolder
{
public:

	Block(const BlockInfo& info);

	// texWorldSize�� ����Ʈ�� y offset�� ���� �ξ� �Ӹ��κ��� �ڷ� ���� �Ѿ�Բ� �̼��ϰ� ������ ����
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
	/// block �̵� �õ�
	/// </summary>
	/// <param name="destBoardCoordX"> : �̵��� destination board coord X ��ǥ </param>
	/// <param name="destBoardCoordY"> : �̵��� destination board coord Y ��ǥ </param>
	/// <returns> �̵� ���� ���� </returns>
	bool Move(const UINT& destBoardCoordX, const UINT& destBoardCoordY);

	/// <summary>
	/// block �̵� �õ�
	/// </summary>
	/// <param name="destCoord"> : �̵��� destination board coord </param>
	/// <returns> �̵� ���� ���� </returns>
	bool Move(const Util::Coord& destCoord);

	/// <summary>
	/// block �̵� �õ�
	/// </summary>
	/// <param name="destination"> : �̵��� ���� Vector2 ��ǥ </param>
	/// <returns> �̵� ���� ���� </returns>
	bool Move(Vector2 destination);

	/* block �̵� �� �̵�ó�� ��� (Called in Update) */
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
	/* ��Ǯ interaction �ǽ� */
	void PlayBushInteraction();

	/* currentlyBushing�� üũ�Ͽ� ��Ǯ interaction handling */
	void HandleBushInteraction();
	
private: /* Collider call back functions */

	void OnColliderPointEnter(ColliderHolder* owner);
	void OnColliderPointStay(ColliderHolder* owner);
	void OnColliderPointExit(ColliderHolder* owner);

	void OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner);
	void OnColliderRectStay(ColliderRect* targetCollider, ColliderHolder* owner);
	void OnColliderRectExit(ColliderRect* targetCollider, ColliderHolder* owner);

private:

	/// <param name="cDirection"> : ���� ĳ���Ͱ� ���ϴ� ���� </param>
	/// <param name="collidedFace"> : ���� ĳ���Ϳ� �浹���� block�� �� ���� </param>
	/// <returns></returns>
	bool IsPushing(const Direction& cDirection, const Direction& collidedFace);

private:
	/* ������ Ȯ���� ������ ���� �õ� */
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

	UINT		hp{1};				// ����� ü��
	Animation*	destroyedAnim{};	// ����� �μ��� �� ����� animation

private: /* Movable block ���� */

	Util::Coord boardPos{};							// ���� Cell ��ǥ
	Vector2		destination{};						// �̵��� ��ġ
	bool		currentlyMoving{};					// ���� �����̴� ������
	float		pushForceAppliedTime{};				// �и� ���� �ð� üũ timer
	const float PUSH_APPLIED_TIME_LIMIT{ 0.2f };	// �и� �ð� threshold

private: /* ��Ǯ block Interaction ���� */

	bool	currentlyBushing{};		// ��Ǯ interaction�� ���������� (ex - bush animation, bush sound play)
	float	bushInteractedTime{};	// ��Ǯ interaction�� ������ �� �ð�

private: /* ������ ����(������ ���� ���� ���� ���� ����) */
	
	/* 
	Block���� �����ϰ� ���� -> �����Ǿ��ٸ� �ش� �������� ItemManager�� �Ѱܼ� ItemManager���� �ϰ������� managing
	������ �Ŵ������� �ϰ� ����, Update, Render�� ����
	*/
	Item* item{};

private:
	string label{}; // Debug label

};
