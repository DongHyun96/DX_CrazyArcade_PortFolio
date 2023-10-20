#pragma once
class MainGame
{
public:
	MainGame();
	~MainGame();

	void Update();

	void Render();
	
	void SetUpImGui();
	void ImGuiNewFrame();

private:
	void DebugMousePos();

private:

	//Scene* scene = nullptr;
};
