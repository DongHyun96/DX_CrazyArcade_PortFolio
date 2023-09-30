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
		file = binReader.ReadWString();
		frameX	= binReader.ReadUINT();
		frameY	= binReader.ReadUINT();
		targetX	= binReader.ReadUINT();
		targetY	= binReader.ReadUINT();
	}

	wstring file{};
	UINT	frameX{};
	UINT	frameY{};
	UINT	targetX{};
	UINT	targetY{};

};

class MapEditor
{
private:

	MapEditor();
	~MapEditor();

public:

	static MapEditor* GetInst()
	{
		static MapEditor singleton;
		return &singleton;
	}

	void Update();
	void Render();

private:

	void UpateObjects();

private:

	void InitCells();
	void InitTileMaps();

	void SelectTileMap();
	void SetTileToWorld();

	void CreateTile(UINT boardX, UINT boardY);
	void CreateTile(const TileInfo& info, UINT boardX, UINT boardY);

private:

	void Save();
	void Load();

private:
	
	// 월드 타일 관련
	Collider*	cells[MAP_ROW][MAP_COL]{};
	Object*		cellTiles[MAP_ROW][MAP_COL]{};
	TileInfo	infos[MAP_ROW][MAP_COL]{};
	
	// 타일맵 메뉴 관련
	vector<pair<Object*, TileInfo>> tileMaps;
	vector<Collider*> tileMapColliders{};
	UINT selectedTIdx{};

	const UINT tileMapCnt = 12;

	const Vector2 cellSize = Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW);

};
