#include "Framework.h"
#include "TextureScene.h"


TextureScene::TextureScene()
{
	knight = new Knight;

	CAMERA->SetTarget(knight);

	background = new Object(L"Knight PNG/Knight_win_02.png");
	background->scale = { 5, 5 };
	background->translation = WIN_CENTER;

	background->zDepth = 0.f;
	knight->zDepth = -5.f;

	background->SetLabel("BackGround");

	renderers.push_back((Renderer*)knight);
	renderers.push_back((Renderer*)background);
}

TextureScene::~TextureScene()
{
	delete knight;
	delete background;
}

void TextureScene::Update()
{
	background->Update();
	knight->Update();
}

void TextureScene::Render()
{
	//sort(renderers.begin(), renderers.end(), [](Renderer* a, Renderer* b) {return dynamic_cast<Transform*>(a)->zDepth > dynamic_cast<Transform*>(b)->zDepth; });

	sort(renderers.begin(), renderers.end(), Util::CompareRendererZorder);

	for (Renderer* r : renderers)
		r->Render();

	//knight->Render();
	//background->Render();

	background->Debug();
}
