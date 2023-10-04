#include "Framework.h"
#include "CollisionScene.h"


CollisionScene::CollisionScene()
{
	for (UINT i = 0; i < 2; i++)
	{
		Collider* collider = new ColliderCircle(50.f);
		collider->translation = WIN_CENTER + Vector2(200.f * i, 0.f);
		collider->SetLabel("ColliderCircle" + to_string(i + 1));

		colliders.push_back(collider);

	}

	for (UINT i = 0; i < 2; i++)
	{
		Collider* collider = new ColliderRect(Vector2(100, 200));
		collider->translation = WIN_CENTER + Vector2(200.f * i, 200.f);
		collider->SetLabel("ColliderRect" + to_string(i + 1));

		colliders.push_back(collider);

	}
}

CollisionScene::~CollisionScene()
{
	for (Collider* collider : colliders)
		delete collider;

	colliders.clear();
}

void CollisionScene::Update()
{
	for (Collider* collider : colliders)
		collider->Update();

	if (colliders[2]->Collision(colliders[3]))
		colliders[2]->SetColor(1, 0, 0);
	else
		colliders[2]->SetColor(0, 1, 0);
}

void CollisionScene::Render()
{
	for (Collider* collider : colliders)
	{
		collider->Render();
		collider->Debug();
	}
}
