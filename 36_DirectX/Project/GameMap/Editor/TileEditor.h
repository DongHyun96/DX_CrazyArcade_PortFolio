#pragma once

struct TileInfo
{
	TileInfo() {}

	TileInfo(wstring file, UINT frameX, UINT frameY, UINT targetX, UINT targetY)
		:file(file), frameX(frameX), frameY(frameY), targetX(targetX), targetY(targetY)
	{
	}

	void SaveData(BinaryWriter& binWriter)
	{
		binWriter.WriteData(file);
		binWriter.WriteData(frameX);
		binWriter.WriteData(frameY);
		binWriter.WriteData(targetX);
		binWriter.WriteData(targetY);
	}

	void ReadAndCopy(BinaryReader& binReader)
	{
		file	= binReader.ReadWString();
		frameX	= binReader.ReadUINT();
		frameY	= binReader.ReadUINT();
		targetX = binReader.ReadUINT();
		targetY = binReader.ReadUINT();
	}

	wstring file{};
	UINT	frameX{};
	UINT	frameY{};
	UINT	targetX{};
	UINT	targetY{};

};

class TileEditor
{
public:
	TileEditor();
	~TileEditor();

	void Update();
	void Render();

private:

	void InitTileMaps();

	void UpdateObjects();

	void SelectTileMap();
	void SetTileToWorld();

	void CreateTile(UINT boardX, UINT boardY);						 // editor에서 edit할 떄의 용도
	void CreateTile(const TileInfo& info, UINT boardX, UINT boardY); // 시작 시 Load할 때 create하는 용도

private:

	void Save();
	void Load();

private:
	
	// 월드 타일 관련
	Object*		cellTiles[MAP_ROW][MAP_COL]{};
	TileInfo	infos[MAP_ROW][MAP_COL]{};
	
	// 타일맵 메뉴 관련
	vector<pair<Object*, TileInfo>> tileMaps;
	vector<Collider*>				tileMapColliders{};
	UINT							selectedTIdx{};

};
