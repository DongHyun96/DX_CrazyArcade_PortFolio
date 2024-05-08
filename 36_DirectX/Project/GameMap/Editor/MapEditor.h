#pragma once

class GameUIManager;

/*
CONCRETE CLASS
TileMapEditor�� BlockMapEditor�� ����
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

private: // ImGui�� ���� ��ɵ�
	
	const string label = "MapEditor";	// Debug label
	EditMode	 mode  = BLOCK_MODE;	// Current editing mode
	
private:
	/* CellColliders ���������� ���� */
	bool renderColliderFlag = true;

private:
	/* GameScene �� �г� ������ �뵵 */
	GameUIManager* uiManager{};

};
