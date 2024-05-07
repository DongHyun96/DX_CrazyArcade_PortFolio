#pragma once

class MapEditor;

/* Tile�� ���� save & load�� ������ */
struct TileInfo
{
	TileInfo() {}

	/// <param name="file"> : Texture file path </param>
	/// <param name="frameX"> : Texture file�� Row ������ �� ���� </param>
	/// <param name="frameY"> : Texture file�� Col ������ �� ���� </param>
	/// <param name="targetX"> : ����� ������ ��ġ�� Row �� </param>
	/// <param name="targetY"> : ����� ������ ��ġ�� Col �� </param>
	TileInfo(wstring file, UINT frameX=1, UINT frameY=1, UINT targetX=1, UINT targetY=1)
		:file(file), frameX(frameX), frameY(frameY), targetX(targetX), targetY(targetY)
	{
	}

	/// <summary>
	/// TileInfo bin ���� �������� ����
	/// </summary>
	/// <param name="binWriter"> : BinaryWriter reference </param>
	void SaveData(BinaryWriter& binWriter)
	{
		binWriter.WriteData(file);
		binWriter.WriteData(frameX);
		binWriter.WriteData(frameY);
		binWriter.WriteData(targetX);
		binWriter.WriteData(targetY);
	}

	/// <summary>
	/// Bin���� ���� ���� �ҷ�����
	/// </summary>
	/// <param name="binReader"> : BinaryReader reference </param>
	void ReadAndCopy(BinaryReader& binReader)
	{
		binReader.ReadAndCopyWstr(file);
		frameX = binReader.ReadUINT();
		frameY = binReader.ReadUINT();
		targetX = binReader.ReadUINT();
		targetY = binReader.ReadUINT();
	}

	wstring		file{};		// Texture file path
	UINT		frameX{};	// ���� ���� cell ��ǥ X
	UINT		frameY{};	// ���� ���� cell ��ǥ Y
	UINT		targetX{};	// Texture ���� ������ ����� ������ ��ġ Row��
	UINT		targetY{};	// Texture ���� ������ ����� ������ ��ġ Col��

};


/* 
Owned by MapEditor
GameManager���� editMode�� Ȱ��ȭ �Ǿ� �ְ�, MapEditor�� mode�� TileEditorMode�� �� ���
*/
class TileEditor
{
public:
	/// <param name="mapEditor"> : TileEditor�� ���� ���� mapEditor </param>
	TileEditor(MapEditor* mapEditor);
	~TileEditor();

	void Update();
	void Render();

private:

	void InitTileMaps();

	void UpdateObjects();

	void SelectTileMap();
	void SetTileToWorld();

	void CreateTile(UINT boardX, UINT boardY);						 // editor���� edit�� ���� �뵵
	void CreateTile(const TileInfo& info, UINT boardX, UINT boardY); // ���� �� Load�� �� create�ϴ� �뵵

private:

	void Save();
	void Load();

private:

	MapEditor* mapEditor{};
	
	// ���� Ÿ�� ����
	Object*		cellTiles[MAP_ROW][MAP_COL]{};
	TileInfo	infos[MAP_ROW][MAP_COL]{};
	
	// Ÿ�ϸ� �޴� ����
	vector<pair<Object*, TileInfo>> tileMaps;
	vector<Collider*>				tileMapColliders{};
	UINT							selectedTIdx{};

};
