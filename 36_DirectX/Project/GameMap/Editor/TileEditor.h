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
CONCRETE CLASS
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
	/* Update all objects */
	void UpdateObjects();

private:
	/* Ÿ�� �޴���ư initialization */
	void InitTileButtons();

private:
	/* Ÿ�� �޴���ư�� ���� ���� Ÿ�� �����ϱ� */
	void SelectTileMap();

	/* ���� Ÿ�� world�� ��ġ */
	void HandleSetTileToWorld();

private:

	/// <summary>
	/// Editor���� ���� ���õ� Ÿ���� world�� ��ġ�� �� ���
	/// </summary>
	/// <param name="boardX"> : ��ġ�� cell pos X�� </param>
	/// <param name="boardY"> : ��ġ�� cell pos Y�� </param>
	void CreateTile(UINT boardX, UINT boardY);

	/// <summary>
	/// EditMode ���� ��, GameManager�� curMapType�� ���� �̸� ����� Tile���� Load�� �� ���
	/// </summary>
	/// <param name="info"> : ���� Ÿ���� ���� </param>
	/// <param name="boardX"> : ��ġ�� cell pos X�� </param>
	/// <param name="boardY"> : ��ġ�� cell pos Y�� </param>
	void CreateTile(const TileInfo& info, UINT boardX, UINT boardY); // ���� �� Load�� �� create�ϴ� �뵵

private:

	/* Save current cellTiles infos */
	void Save();

	/* Load current gameMap cell Tiles infos */
	void Load();

private:
	/* Owner of this class */
	MapEditor* mapEditor{};

private: /* ���� Ÿ�� ���� */
	
	Object*		cellTiles[MAP_ROW][MAP_COL]{};	// World�� ��ġ�� Ÿ�� ��ü��
	TileInfo	infos[MAP_ROW][MAP_COL]{};		// ���� world�� �� cell�� ��ġ�� Ÿ�ϵ��� infos
	
private: /* Ÿ�ϸʸ޴� ��ư ���� */
	vector<pair<Object*, TileInfo>> tileMaps;			// vector< <Ÿ�ϸʹ�ư rendering�� ��ü, �ش��ϴ� TileInfo> >
	vector<Collider*>				tileMapColliders{};	// Ÿ�ϸʹ�ư Collider (���콺�� Collision ó��)
	UINT							selectedTIdx{};		// ���� ���õ� Ÿ�ϸʹ�ư index

};
