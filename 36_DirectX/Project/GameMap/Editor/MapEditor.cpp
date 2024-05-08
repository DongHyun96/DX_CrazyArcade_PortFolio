#include "Framework.h"
#include "MapEditor.h"


MapEditor::MapEditor()
{
	InitCellColliders();

	tileEditor = new TileEditor(this);
	blockEditor = new BlockEditor(this);

	uiManager = new GameUIManager;
}

MapEditor::~MapEditor()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
			delete cellColliders[i][j];
	}

	delete tileEditor;
	delete blockEditor;

	delete uiManager;
}

void MapEditor::Update()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
			cellColliders[i][j]->Update();
	}

	tileEditor->Update();
	blockEditor->Update();
	uiManager->Update();
}

void MapEditor::Render()
{
	if (renderColliderFlag)
	{
		for (UINT i = 0; i < MAP_ROW; i++)
		{
			for (UINT j = 0; j < MAP_COL; j++)
				cellColliders[i][j]->Render();
		}
	}

	tileEditor->Render();
	blockEditor->Render();
	uiManager->Render();

	Debug();
}

void MapEditor::InitCellColliders()
{
	for (UINT i = 0; i < MAP_ROW; i++)
	{
		for (UINT j = 0; j < MAP_COL; j++)
		{
			cellColliders[i][j] = new ColliderRect(CELL_WORLD_SIZE);
			Util::SetTransformToGameBoard(cellColliders[i][j], j, i);
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

	ImGui::Begin("RenderCollider");
	ImGui::Checkbox("RenderCollider", &renderColliderFlag);
	ImGui::End();


}

