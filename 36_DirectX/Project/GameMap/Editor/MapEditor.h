#pragma once

class GameUIManager;

/*
CONCRETE CLASS
TileMapEditor와 BlockMapEditor를 소유
*/
class MapEditor
{
public:
	/* Current editing mode */
	enum EditMode
	{
		TILE_MODE,
		BLOCK_MODE
	};

public:

	MapEditor();
	~MapEditor();

	void Update();
	void Render();

public:
	EditMode GetMode()			     const { return mode; }
	bool	 GetRenderColliderFlag() const { return renderColliderFlag; }

private:

	void InitCellColliders();

private:

	void Debug();

public:
	/* Each cell's colliders */
	Collider* cellColliders[MAP_ROW][MAP_COL]{};

private:

	TileEditor*		tileEditor{};
	BlockEditor*	blockEditor{};

private: // ImGui를 통한 기능들
	
	const string label = "MapEditor";	// Debug label
	EditMode	 mode  = BLOCK_MODE;	// Current editing mode
	
private:
	/* CellColliders 렌더링할지 여부 */
	bool renderColliderFlag = true;

private:
	/* GameScene 옆 패널 렌더링 용도 */
	GameUIManager* uiManager{};

};
