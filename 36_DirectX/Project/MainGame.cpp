#include "Framework.h"
#include "MainGame.h"


MainGame::MainGame()
{
	SetUpImGui();

	//scene = new TutorialScene;
	//scene = new SRTScene;
	//scene = new SolarScene;

	//scene = new TextureScene;
	//scene = new CollisionScene;
	scene = new GameScene;

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

	scene->Update();
}

void MainGame::Render()
{
	ImGuiNewFrame();

	Environment::GetInstance()->Set();
	Camera::GetInstance()->Set();

	scene->Render();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void MainGame::SetUpImGui()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
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

