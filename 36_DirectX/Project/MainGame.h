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

	//Scene* scene = nullptr;
};
