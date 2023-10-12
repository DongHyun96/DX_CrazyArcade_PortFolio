#include "Framework.h"
#include "DartManager.h"


DartManager::DartManager()
{
	for (UINT i = 0; i < POOL_CNT; i++)
		darts.push_back(new Dart);
}

DartManager::~DartManager()
{
	for (Dart* dart : darts)
		delete dart;
}

void DartManager::Update()
{
	for (Dart* dart : darts)
		dart->Update();

	HandleCollision();
}

void DartManager::Render()
{
	for (Dart* dart : darts)
		dart->Render();
}

void DartManager::Spawn(const Vector2& spawnPos, const Direction& fireDirection)
{
	for (Dart* dart : darts)
	{
		if (dart->GetIsActive()) continue;

		dart->Spawn(spawnPos, fireDirection);
		return;
	}
}

void DartManager::HandleCollision()
{
	// Block과의 충돌은 blockManager에서 담당

	for (Dart* dart : darts)
	{
		if (!dart->GetIsActive()) continue;
		
		for (Balloon* balloon : GM->GetBalloonManager()->GetBalloons())
		{
			if (!balloon->Active()) continue;

			balloon->GetBody()->AABBCollision(balloon->GetBody(), balloon);
		}
	}
}
