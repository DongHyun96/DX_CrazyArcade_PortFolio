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
	Animation* destroyedAnim{}; // BlockManager에서 받아옴

	// Movable 관련
	Vector2 destination{};
	bool currentlyMoving{};

	// Bush Interaction 관련
	bool currentlyBushing{};
	float interactTime{};

};
