#pragma once

class MapEditor;


/*
CONCRETE CLASS
Owned by MapEditor
GameManager에서 editMode가 활성화 되어 있고, MapEditor의 mode가 BlockEditorMode일 때 사용
*/
class BlockEditor
{
public:
	BlockEditor(MapEditor* mapEditor);
	~BlockEditor();

	void Update();
	void Render();


private:
	/* Update all objects */
	void UpdateObjects();

private:
	/* 블록 메뉴버튼 initialization */
	void InitBlockButtons();

private:
	/* 블록 메뉴버튼을 통해 현재 블록 선택하기 */
	void SelectBlockMap();

	/* 현재 블록 world에 배치 */
	void SetBlockToWorld();

private:
	/// <summary>
	/// Editor에서 현재 선택된 블록을 world에 배치할 때 사용
	/// </summary>
	/// <param name="boardXY"> : 배치될 cell pos 좌표 </param>
	void CreateBlock(Util::Coord boardXY);

	/// <summary>
	/// EditMode 시작 시, GameManager의 curMapType에 따른 미리 저장된 Block들을 Load
	/// </summary>
	/// <param name="info"> : 만들 블록의 정보</param>
	/// <param name="boardXY"> : 배치될 cell pos 좌표 </param>
	void CreateBlock(const BlockInfo& info, Util::Coord boardXY); 


	/// <summary>
	/// World에 배치된 block 지우기
	/// </summary>
	/// <param name="boardXY"> 지울 block의 cell pos 좌표 </param>
	void EraseBlock(const Util::Coord& boardXY);
																  
private:

	/* Save current cellBlocks infos */
	void Save();

	/* Load current gameMap cell Blocks infos */
	void Load();

/***************************************************************************************************
*                                          Member variables                                        *
****************************************************************************************************/

private:

	/* Owner of this class */
	MapEditor* mapEditor{};

private: /* World에 배치된 블록 관련 */
	Block*		cellBlocks[MAP_ROW][MAP_COL]{};	// World에 배치된 블록 객체들
	BlockInfo	infos[MAP_ROW][MAP_COL]{};		// 현재 world의 각 cell에 배치된 블록들의 infos

private: /* 블록맵 버튼 관련 */
	vector<pair<Block*, BlockInfo>> blockMaps{};			// vector< <블록맵버튼 rendering할 객체, 해당하는 BlockInfo> >
	vector<Collider*>				blockMapColliders{};	// 블록맵버튼 Collider (마우스와 Collision 처리)
	UINT							selectedIdx{};			// 현재 선택된 블록맵버튼 index


};

