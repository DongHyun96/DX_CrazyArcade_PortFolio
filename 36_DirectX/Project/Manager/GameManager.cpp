#include "Framework.h"
#include "GameManager.h"


GameManager::GameManager()
{
	gameFieldTransform = new Transform;

	gameFieldTransform->scale = Vector2(0.76f, 0.88f);
	gameFieldTransform->translation = Vector2(768.f, 538.f);

}

GameManager::~GameManager()
{
	delete gameFieldTransform;
}

void GameManager::Update()
{
	gameFieldTransform->Update();
}
