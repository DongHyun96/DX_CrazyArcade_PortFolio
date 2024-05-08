#pragma once

class MapEditor;

/* Tile에 대해 save & load할 정보들 */
struct TileInfo
{
	TileInfo() {}

	/// <param name="file"> : Texture file path </param>
	/// <param name="frameX"> : Texture file의 Row 프레임 총 개수 </param>
	/// <param name="frameY"> : Texture file의 Col 프레임 총 개수 </param>
	/// <param name="targetX"> : 사용할 프레임 위치의 Row 값 </param>
	/// <param name="targetY"> : 사용할 프레임 위치의 Col 값 </param>
	TileInfo(wstring file, UINT frameX=1, UINT frameY=1, UINT targetX=1, UINT targetY=1)
		:file(file), frameX(frameX), frameY(frameY), targetX(targetX), targetY(targetY)
	{
	}

	/// <summary>
	/// TileInfo bin 파일 내용으로 저장
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
	/// Bin파일 저장 내용 불러오기
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
	UINT		frameX{};	// 게임 보드 cell 좌표 X
	UINT		frameY{};	// 게임 보드 cell 좌표 Y
	UINT		targetX{};	// Texture 파일 내에서 사용할 프레임 위치 Row값
	UINT		targetY{};	// Texture 파일 내에서 사용할 프레임 위치 Col값

};


/* 
CONCRETE CLASS
Owned by MapEditor
GameManager에서 editMode가 활성화 되어 있고, MapEditor의 mode가 TileEditorMode일 때 사용
*/
class TileEditor
{
public:
	/// <param name="mapEditor"> : TileEditor를 소유 중인 mapEditor </param>
	TileEditor(MapEditor* mapEditor);
	~TileEditor();

	void Update();
	void Render();

private:
	/* Update all objects */
	void UpdateObjects();

private:
	/* 타일 메뉴버튼 initialization */
	void InitTileButtons();

private:
	/* 타일 메뉴버튼을 통해 현재 타일 선택하기 */
	void SelectTileMap();

	/* 현재 타일 world에 배치 */
	void HandleSetTileToWorld();

private:

	/// <summary>
	/// Editor에서 현재 선택된 타일을 world에 배치할 때 사용
	/// </summary>
	/// <param name="boardX"> : 배치될 cell pos X값 </param>
	/// <param name="boardY"> : 배치될 cell pos Y값 </param>
	void CreateTile(UINT boardX, UINT boardY);

	/// <summary>
	/// EditMode 시작 시, GameManager의 curMapType에 따른 미리 저장된 Tile들을 Load할 때 사용
	/// </summary>
	/// <param name="info"> : 만들 타일의 정보 </param>
	/// <param name="boardX"> : 배치될 cell pos X값 </param>
	/// <param name="boardY"> : 배치될 cell pos Y값 </param>
	void CreateTile(const TileInfo& info, UINT boardX, UINT boardY); // 시작 시 Load할 때 create하는 용도

private:

	/* Save current cellTiles infos */
	void Save();

	/* Load current gameMap cell Tiles infos */
	void Load();

private:
	/* Owner of this class */
	MapEditor* mapEditor{};

private: /* 월드 타일 관련 */
	
	Object*		cellTiles[MAP_ROW][MAP_COL]{};	// World에 배치된 타일 객체들
	TileInfo	infos[MAP_ROW][MAP_COL]{};		// 현재 world의 각 cell에 배치된 타일들의 infos
	
private: /* 타일맵메뉴 버튼 관련 */
	vector<pair<Object*, TileInfo>> tileMaps;			// vector< <타일맵버튼 rendering할 객체, 해당하는 TileInfo> >
	vector<Collider*>				tileMapColliders{};	// 타일맵버튼 Collider (마우스와 Collision 처리)
	UINT							selectedTIdx{};		// 현재 선택된 타일맵버튼 index

};
