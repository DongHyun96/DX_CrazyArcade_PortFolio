#include "Framework.h"
#include "IntroScene.h"


IntroScene::IntroScene()
{
	//rgb(199, 0, 57)
	//rgb(12, 53, 106)
	FONT->Add("InstructionFont", L"배찌체", Util::ConvertRGB_UINT_To_Float(199, 0, 57),
		50.f, DWRITE_PARAGRAPH_ALIGNMENT_NEAR, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_BOLD);

	background = new Object(WIN_SIZE, L"InGame/UI/IntroScene/Back_Loding.bmp");
	background->translation = WIN_CENTER;

	desc = new Object(L"InGame/UI/IntroScene/desc.png");
	desc->scale = { 1.3f, 1.3f };
	desc->translation = { WIN_CENTER.x, 730.f };
	desc->zDepth = -0.5f;

	for (UINT i = 0; i < 5; i++)
	{
		characters.push_back(new Object(L"InGame/UI/IntroScene/UI_Loading" + to_wstring(i + 2) + L".png"));
		characters[i]->translation = WIN_CENTER;
		characters[i]->scale = { 0.f, 0.f };
		characters[i]->zDepth = -1.f;
	}

	destPos =
	{
		{515, 828},
		{1317, 822},
		{381, 548},
		{1357, 459},
		{WIN_CENTER.x, 914}
	};

	SOUND->Play("IntroBGM", 1.f);
}

IntroScene::~IntroScene()
{
	delete background;
	delete desc;

	for (Object* obj : characters)
		delete obj;
}

void IntroScene::Update()
{
	if (KEY_DOWN(VK_LBUTTON) && GetForegroundWindow() == hWnd)
	{
		clicked = true;
	}


	background->Update();
	desc->Update();

	for (Object* character : characters)
		character->Update();

	if (clicked)
	{
		timer += Time::Delta();

		for (UINT i = 0; i < 5; i++)
		{
			if (timer > SPAWN_TICK * i)
			{
				characters[i]->translation = Vector2::Lerp(characters[i]->translation, destPos[i], 10.f * Time::Delta());
				characters[i]->scale = Vector2::Lerp(characters[i]->scale, { 1.f, 1.f }, 10.f * Time::Delta());
			}
		}

		if (Vector2::Distance(characters.back()->translation, destPos.back()) < 0.1f) // Scene 전환
		{
			SOUND->Stop("IntroBGM");
			SM->SetCurScene(LOBBY_SCENE);
		}
	}

}


void IntroScene::Render()
{
	background->Render();

	if (clicked)
	{
		for (Object* character : characters)
			character->Render();

		return;
	}

	desc->Render();
	

	FONT->RenderText(L"아무 곳이나 클릭하여 시작!", "InstructionFont", Util::ConvertDxPosToAPIPos({ WIN_CENTER.x, 327.f}));
	//\nCLICK ANYWHERE TO START!
}
