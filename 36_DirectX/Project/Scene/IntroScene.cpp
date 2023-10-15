#include "Framework.h"
#include "IntroScene.h"


IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}

void IntroScene::Update()
{
	if (KEY_DOWN(VK_SPACE))
		SceneManager::GetInst()->SetCurScene(GAME_SCENE);
}


void IntroScene::Render()
{
}
