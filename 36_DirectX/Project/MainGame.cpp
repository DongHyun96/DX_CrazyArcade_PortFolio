#include "Framework.h"
#include "MainGame.h"


MainGame::MainGame()
{
	srand(time(NULL));

	SetUpImGui();

	//scene = new CollisionScene;
	scene = new GameScene;

	//rgb(4, 54, 74)
	//rgb(216, 0, 50)

	FONT->Add("D2Coding", L"D2Coding", {1.f, 1.f, 1.f}, 30.f, DWRITE_PARAGRAPH_ALIGNMENT_NEAR, DWRITE_TEXT_ALIGNMENT_TRAILING, DWRITE_FONT_WEIGHT_BOLD);

	FONT->Add("BazziFont", L"배찌체", { 1.f, 1.f, 1.f }, 30.f, DWRITE_PARAGRAPH_ALIGNMENT_NEAR, DWRITE_TEXT_ALIGNMENT_CENTER);
	FONT->Add("BazziFontBold", L"배찌체", { 1.f, 1.f, 1.f }, 30.f, DWRITE_PARAGRAPH_ALIGNMENT_NEAR, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_BOLD);

}

MainGame::~MainGame()
{
	delete scene;

	Device::Delete();
	Environment::Delete();

	Time::Delete();
	Keyboard::Delete();
	Texture::Delete();
	Camera::Delete();
	Font::Delete();
	SoundManager::Delete();

	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void MainGame::Update()
{
	Time::GetInstance()->Update();
	Keyboard::GetInstance()->Update();
	Camera::GetInstance()->Update();

	SOUND->Update();

	UI->Update();

	scene->Update();

	if (KEY_DOWN(VK_TAB))
		ToggleHideUI();
}

void MainGame::Render()
{
	ImGuiNewFrame();

	FONT->GetDC()->BeginDraw(); // Begin End 사이에서 render해야함

	Environment::GetInstance()->Set();
	Camera::GetInstance()->Set();

	UI->Render();
	scene->Render();

	if (!hiddenInGame)
	{
		Time::GetInstance()->Render();
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	FONT->GetDC()->EndDraw();
	ImGui::EndFrame();
}

void MainGame::SetUpImGui()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);

}

void MainGame::ImGuiNewFrame()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

