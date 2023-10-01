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
	knight->Render();
	background->Render();

	background->Debug();
}
