#include "Framework.h"
#include "MapEditor.h"


MapEditor::MapEditor()
{
	InitCells();

	tileEditor = new TileEditor;
	blockEditor = new BlockEditor;
}

MapEditor::~MapEditor()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
			delete cells[i][j];
	}

	delete tileEditor;
	delete blockEditor;
}

void MapEditor::Update()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
			cells[i][j]->Update();
	}

	tileEditor->Update();
	blockEditor->Update();
}

void MapEditor::Render()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
			cells[i][j]->Render();
	}

	tileEditor->Render();
	blockEditor->Render();

	Debug();
}

void MapEditor::InitCells()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			cells[i][j] = new ColliderRect(CELL_WORLD_SIZE);
			Util::SetTransformToGameBoard(cells[i][j], j, i);
		}
	}
}

void MapEditor::Debug()
{
	assert(!label.empty());

	//if (ImGui::BeginMenu(label.c_str()))
	//{

	//	ImGui::EndMenu();
	//}

	ImGui::Begin("EditMode");

	const char* enumNames[] = { "TILE_MODE", "BLOCK_MODE" };
	int selectedItem = static_cast<int>(mode);

	if (ImGui::Combo("Select mode", &selectedItem, enumNames, IM_ARRAYSIZE(enumNames))) {
		// The user selected a new enum value, update the currentEnumValue accordingly.
		mode = static_cast<EditMode>(selectedItem);
	}

	ImGui::End();


}

