#pragma once


class MapEditor
{
public:
	enum EditMode
	{
		TILE_MODE,
		BLOCK_MODE
	};

private:

	MapEditor();
	~MapEditor();

public:

	static MapEditor* GetInst()
	{
		static MapEditor singleton;
		return &singleton;
	}

public:

	void Update();
	void Render();

public:
	EditMode GetMode() const { return mode; }
	bool GetRenderColliderFlag() const { return renderColliderFlag; }

	//Collider* (*GetCells())[MAP_COL] { return cells; }

private:

	void InitCells();
	void Debug();

public:
	Collider* cells[MAP_ROW][MAP_COL]{};

private:

	TileEditor* tileEditor{};
	BlockEditor* blockEditor{};

	

private: // ImGui를 통한 기능들
	
	const string label{"MapEditor"};
	EditMode mode = BLOCK_MODE;
	
	bool renderColliderFlag = true;

};
