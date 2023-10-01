#pragma once

struct BlockInfo
{
	BlockInfo() {}

	BlockInfo(wstring file, Util::Coord boardXY, Util::Coord frameXY, Util::Coord targetXY, BlockProperty bProp, Vector2 texWorldSize = CELL_WORLD_SIZE)
		:file(file), boardXY(boardXY), frameXY(frameXY), targetXY(targetXY), bProp(bProp), texWorldSize(texWorldSize)
	{}

	wstring			file{};
	Util::Coord		boardXY{};
	Util::Coord		frameXY{};
	Util::Coord		targetXY{};
	BlockProperty	bProp{};
	Vector2			texWorldSize{ CELL_WORLD_SIZE };
};

class BlockEditor
{
public:
	BlockEditor();
	~BlockEditor();

	void Update();
	void Render();

private:

	void InitBlockMaps();

	void UpdateObjects();

	void SelectBlockMap();
	void SetBlockToWorld();

	void CreateBlock(Util::Coord boardXY);
	void CreateBlock(const BlockInfo& info, Util::Coord boardXY);

private:

	void Save();
	void Load();

private:

	// 월드에 배치된 블록들 관련
	vector<Block*>		cellBlocks{};
	vector<BlockInfo>	infos{};

	// 블록맵 메뉴 관련
	vector<pair<Block*, BlockInfo>> blockMaps{};
	vector<Collider*>				blockMapColliders{};
	UINT							selectedIdx{};
};

