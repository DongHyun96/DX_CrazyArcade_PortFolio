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

	void InitTileMaps();

	void UpdateObjects();

	void SelectTileMap();
	void SetTileToWorld();

	void CreateTile(UINT boardX, UINT boardY);						 // editor에서 edit할 때의 용도
	void CreateTile(const TileInfo& info, UINT boardX, UINT boardY); // 시작 시 Load할 때 create하는 용도

private:

	void Save();
	void Load();

private:

	MapEditor* mapEditor{};
	
	// 월드 타일 관련
	Object*		cellTiles[MAP_ROW][MAP_COL]{};
	TileInfo	infos[MAP_ROW][MAP_COL]{};
	
	// 타일맵 메뉴 관련
	vector<pair<Object*, TileInfo>> tileMaps;
	vector<Collider*>				tileMapColliders{};
	UINT							selectedTIdx{};

};
