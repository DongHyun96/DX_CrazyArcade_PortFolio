#pragma once

class MapEditor;


/*
CONCRETE CLASS
Owned by MapEditor
GameManager���� editMode�� Ȱ��ȭ �Ǿ� �ְ�, MapEditor�� mode�� BlockEditorMode�� �� ���
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
	/* ��� �޴���ư initialization */
	void InitBlockButtons();

private:
	/* ��� �޴���ư�� ���� ���� ��� �����ϱ� */
	void SelectBlockMap();

	/* ���� ��� world�� ��ġ */
	void SetBlockToWorld();

private:
	/// <summary>
	/// Editor���� ���� ���õ� ����� world�� ��ġ�� �� ���
	/// </summary>
	/// <param name="boardXY"> : ��ġ�� cell pos ��ǥ </param>
	void CreateBlock(Util::Coord boardXY);

	/// <summary>
	/// EditMode ���� ��, GameManager�� curMapType�� ���� �̸� ����� Block���� Load
	/// </summary>
	/// <param name="info"> : ���� ����� ����</param>
	/// <param name="boardXY"> : ��ġ�� cell pos ��ǥ </param>
	void CreateBlock(const BlockInfo& info, Util::Coord boardXY); 


	/// <summary>
	/// World�� ��ġ�� block �����
	/// </summary>
	/// <param name="boardXY"> ���� block�� cell pos ��ǥ </param>
	void EraseBlock(const Util::Coord& boardXY);
																  
private:

	/* Save current cellBlocks infos */
	void Save();

	/* Load current gameMap cell Blocks infos */
	void Load();

private:

	/* Owner of this class */
	MapEditor* mapEditor{};

private: /* World�� ��ġ�� ��� ���� */
	Block*		cellBlocks[MAP_ROW][MAP_COL]{};	// World�� ��ġ�� ��� ��ü��
	BlockInfo	infos[MAP_ROW][MAP_COL]{};		// ���� world�� �� cell�� ��ġ�� ��ϵ��� infos

private: /* ��ϸ� ��ư ���� */
	vector<pair<Block*, BlockInfo>> blockMaps{};			// vector< <��ϸʹ�ư rendering�� ��ü, �ش��ϴ� BlockInfo> >
	vector<Collider*>				blockMapColliders{};	// ��ϸʹ�ư Collider (���콺�� Collision ó��)
	UINT							selectedIdx{};			// ���� ���õ� ��ϸʹ�ư index


};

