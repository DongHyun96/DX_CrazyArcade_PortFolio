#pragma once

#define Y_OFFSET 20.f

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

class Block
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
	void SetLabel(const string& label) { this->label = label; }

public:

	Collider* GetBody() { return rectBody; }
	Vector2 GetTranslation() const { return rectBody->translation; }

	bool& IsActive() { return isActive; }

private:

	bool Move(Vector2 destination);
	void Move();

	void HandleBushInteract();

private:
	
	string label{};

	Collider*	rectBody{};
	Object*		texObj{};

	bool isActive = true;

	bool breakable{};
	bool movable{};
	bool hidable{};

	UINT hp{};
	Animation* destroyedAnim{}; // BlockManager���� �޾ƿ�

	// Movable ����
	Vector2 destination{};
	bool currentlyMoving{};

	// Bush Interaction ����
	bool currentlyBushing{};
	float interactTime{};

};
