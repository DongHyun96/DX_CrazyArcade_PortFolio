#pragma once



class BlockEditor
{
public:
	BlockEditor();
	~BlockEditor();

	void Update();
	void Render();

public:
	

private:

	void InitBlockMaps();

	void UpdateObjects();

	void SelectBlockMap();
	void SetBlockToWorld();

	void CreateBlock(Util::Coord boardXY);						  // editor에서 edit할 떄의 용도
	void CreateBlock(const BlockInfo& info, Util::Coord boardXY); // 시작 시 Load할 때 create하는 용도
	void EraseBlock(const Util::Coord& boardXY);
																  
private:

	void Save();
	void Load();

private:

	// 월드에 배치된 블록들 관련
	Block*		cellBlocks[MAP_ROW][MAP_COL]{};
	BlockInfo	infos[MAP_ROW][MAP_COL]{};


	// 블록맵 메뉴 관련
	vector<pair<Block*, BlockInfo>> blockMaps{};
	vector<Collider*>				blockMapColliders{};
	UINT							selectedIdx{};


};

