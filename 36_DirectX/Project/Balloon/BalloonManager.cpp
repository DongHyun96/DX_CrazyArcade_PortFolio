#include "Framework.h"
#include "BalloonManager.h"


BalloonManager::BalloonManager()
{
	for (UINT i = 0; i < POOL_CNT; i++)
	{
		balloons.push_back(new Balloon);
	}
}

BalloonManager::~BalloonManager()
{
	for (Balloon* balloon : balloons)
		delete balloon;
}

void BalloonManager::Update()
{
	Character* player = GM->GetPlayer();

	for (Balloon* balloon : balloons)
	{
		if (!balloon->Active())
			continue;

		balloon->Update();
		balloon->GetBody()->OBBCollision(player->GetBody(), (Transform*)player);
	}
}

void BalloonManager::Render()
{
	for (Balloon* balloon : balloons)
		balloon->Render();
}

bool BalloonManager::Spawn(const Util::Coord& spawnCoord)
{
	for (Balloon* balloon : balloons)
	{
		if (balloon->Active())
			continue;

		return balloon->Spawn(spawnCoord);
	}
	return false;
}

bool BalloonManager::Spawn(const Vector2& spawnPos)
{
	for (Balloon* balloon : balloons)
	{
		if (balloon->Active())
			continue;

		return balloon->Spawn(spawnPos);
	}

	return false;
}
