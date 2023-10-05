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

	void CreateBlock(Util::Coord boardXY);						  // editor���� edit�� ���� �뵵
	void CreateBlock(const BlockInfo& info, Util::Coord boardXY); // ���� �� Load�� �� create�ϴ� �뵵
	void EraseBlock(const Util::Coord& boardXY);
																  
private:

	void Save();
	void Load();

private:

	// ���忡 ��ġ�� ��ϵ� ����
	Block*		cellBlocks[MAP_ROW][MAP_COL]{};
	BlockInfo	infos[MAP_ROW][MAP_COL]{};


	// ��ϸ� �޴� ����
	vector<pair<Block*, BlockInfo>> blockMaps{};
	vector<Collider*>				blockMapColliders{};
	UINT							selectedIdx{};


};

