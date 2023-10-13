#include "Framework.h"
#include "UIManager.h"


UIManager::UIManager()
{
	mainUI = new Object(WIN_SIZE, L"InGame/UI/mapToolMap.png");
	//mainUI = new Object(WIN_SIZE, L"InGame/UI/map.png");

	mainUI->translation = WIN_CENTER;
	mainUI->zDepth = FAR_Z - 1;

	itemUI = new Object(L"Ingame/UI/ItemUI.png");
	itemUI->translation = {1727, 175};
	itemUI->scale = { 2.0f, 1.2f };
	itemUI->zDepth = FAR_Z - 2;


}

UIManager::~UIManager()
{
	delete mainUI;
	delete itemUI;
}

void UIManager::Update()
{
	mainUI->Update();
	itemUI->Update();

}

void UIManager::Render()
{
	mainUI->Render();
	itemUI->Render();

	Debug();
}

void UIManager::Debug()
{
	//if (ImGui::BeginMenu("UIManager"))
	//{
	//	ImGui::InputFloat2("MousePos", (float*)&mousePos);
	//	

	//	ImGui::EndMenu();
	//}

	// ImGui::InputFloat("Y", &itemUI->GetSize().y);
	
	ImGui::BeginGroup();

	ImGui::Begin("MousePos");
	ImGui::InputFloat2("XY", (float*)&mousePos);
	Vector2 size = itemUI->GetSize();
	ImGui::InputFloat2("XY", (float*)&size);
	ImGui::End();

	ImGui::EndGroup();

}
