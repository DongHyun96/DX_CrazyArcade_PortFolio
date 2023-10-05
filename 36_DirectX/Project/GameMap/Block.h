#pragma once

#define Y_OFFSET 20.f

class Character;
class Player;

enum Direction
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_NONE
};


struct BlockProperty
{
	bool breakable{};
	bool movable{};
	bool hidable{};
};

struct BlockInfo
{
	BlockInfo() {}

	BlockInfo(wstring file, Util::Coord boardXY, Util::Coord frameXY, Util::Coord targetXY, BlockProperty bProp, Vector2 texWorldSize = CELL_WORLD_SIZE)
		:file(file), boardXY(boardXY), frameXY(frameXY), targetXY(targetXY), bProp(bProp), texWorldSize(texWorldSize)
	{
		initialized = true;
	}

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

	void ReadAndCopy(BinaryReader& binReader)
	{
		initialized			= binReader.ReadInt();
		file				= binReader.ReadWString();
		boardXY				= binReader.ReadCoord();
		frameXY				= binReader.ReadCoord();
		targetXY			= binReader.ReadCoord();
		bProp.breakable		= binReader.ReadInt();
		bProp.movable		= binReader.ReadInt();
		bProp.hidable		= binReader.ReadInt();
		texWorldSize		= binReader.ReadVector2();
	}

	bool initialized{};

	wstring			file{};
	Util::Coord		boardXY{};
	Util::Coord		frameXY{};
	Util::Coord		targetXY{};
	BlockProperty	bProp{};
	Vector2			texWorldSize{ CELL_WORLD_SIZE };
};

class Block : public Transform
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

	void PlayBushInteraction();

	bool Move(const UINT& destBoardCoordX, const UINT& destBoardCoordY);
	bool Move(const Util::Coord& destCoord);

	void ApplyDamage();

	void Debug();
	void Debug(const string& label);
	void SetLabel(const string& label) { this->label = label; }

public:

	ColliderRect* GetBody() { return rectBody; }
	Vector2 GetTranslation() const { return rectBody->translation; }
	
	void SetBoardPos(const Util::Coord& coord) { this->boardPos = coord; }
	Util::Coord GetBoardPos() const { return boardPos; }

	bool& IsActive() { return isActive; }
	bool IsMovable() const { return movable; }
	bool IsBreakable() const { return breakable; }
	bool IsHidable() const { return hidable; }

	void SetVisible(const bool& visible) { this->visible = visible; }

private:
	
	// Move TODO : ������ ���� �ű��

	bool Move(Vector2 destination);

	void Move(); // Use UpdateTime

	void HandleBushInteract();
	
private:

	void OnColliderPointEnter(Transform* owner);
	void OnColliderPointStay(Transform* owner);
	void OnColliderPointExit(Transform* owner);

	void OnColliderRectEnter(ColliderRect* targetCollider, Transform* owner);
	void OnColliderRectStay(ColliderRect* targetCollider, Transform* owner);
	void OnColliderRectExit(ColliderRect* targetCollider, Transform* owner);

	Direction GetCollidedDirection(ColliderRect* collider);

	void HandleCommonCollision(ColliderRect* targetBody);

	bool IsPushing(const Direction& cDirection, const Direction& collidedFace);

private:
	
	string label{};

	ColliderRect*	rectBody{};
	Object*			texObj{};

	bool isActive = true;

	bool breakable{};
	bool movable{};
	bool hidable{};

	bool visible{ true };

	UINT hp{};
	Animation* destroyedAnim{}; // BlockManager���� �޾ƿ�

	// Movable ����
	Util::Coord boardPos{};
	Vector2		destination{};
	bool		currentlyMoving{};
	float		appliedTime{};
	const float appliedTimeLimit{ 0.2f };

	// Bush Interaction ����
	bool	currentlyBushing{};
	float	interactTime{};

};
