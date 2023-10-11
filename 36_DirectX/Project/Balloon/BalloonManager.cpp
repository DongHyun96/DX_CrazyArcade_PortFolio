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
		balloon->GetBody()->OBBCollision(player->GetBody(), (ColliderHolder*)player);
	}

	Balloon::SetExplodeSoundPlayed(false);
}

void BalloonManager::Render()
{
	for (Balloon* balloon : balloons)
		balloon->Render();
}

bool BalloonManager::Spawn(const Util::Coord& spawnCoord, Character* owner)
{
	// 우주선 때문에 해당 위치에 블록(Hidable 제외)이 있다면 spawn시킬 수 없음
	Block* block = GM->GetBlockManager()->GetCoordBlock(spawnCoord);

	if (block)
	{
		if (block->IsActive() && !block->IsHidable()) return false;
	}

	for (Balloon* balloon : balloons)
	{
		if (balloon->Active())
			continue;

		return balloon->Spawn(spawnCoord, owner);
	}

	return false;
}
