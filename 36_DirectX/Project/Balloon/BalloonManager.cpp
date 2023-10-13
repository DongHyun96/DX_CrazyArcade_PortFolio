#include "Framework.h"
#include "BalloonManager.h"


BalloonManager::BalloonManager()
{
	for (UINT i = 0; i < POOL_CNT; i++)
	{
		Animation* normalBalloonAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Balloon/1.png", 4, 1, 4, 0.15f);
		normalBalloons.push_back(new Balloon(normalBalloonAnim));
	}

	for (UINT i = 0; i < TIMERB_POOL_CNT; i++)
	{
		Animation* timerBalloonAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Item/TimerBallon.png", 3, 1, 3, 0.15f);
		timerBalloons.push_back(new TimerBalloon(timerBalloonAnim));
	}
}

BalloonManager::~BalloonManager()
{
	for (Balloon* balloon : normalBalloons)
		delete balloon;

	for (TimerBalloon* t_balloon : timerBalloons)
		delete t_balloon;
}

void BalloonManager::Update()
{
	Character* player = GM->GetPlayer();

	for (Balloon* balloon : normalBalloons)
	{
		if (!balloon->Active())
			continue;

		balloon->Update();
		balloon->GetBody()->AABBCollision(player->GetBody(), (ColliderHolder*)player);
	}

	for (TimerBalloon* t_balloon : timerBalloons)
	{
		if (!t_balloon->Active())
			continue;

		t_balloon->Update();
		t_balloon->GetBody()->AABBCollision(player->GetBody(), player);
	}

	Balloon::SetExplodeSoundPlayed(false);
}

void BalloonManager::Render()
{
	for (Balloon* balloon : normalBalloons)
		balloon->Render();

	for (TimerBalloon* t_balloon : timerBalloons)
		t_balloon->Render();

}

bool BalloonManager::Spawn(const Util::Coord& spawnCoord, Character* owner, const bool& isNormalBalloon)
{
	// ���ּ� ������ �ش� ��ġ�� ���(Hidable ����)�� �ִٸ� spawn��ų �� ����
	Block* block = GM->GetBlockManager()->GetCoordBlock(spawnCoord);

	if (block)
	{
		if (block->IsActive() && !block->IsHidable()) return false;
	}

	if (isNormalBalloon)
	{
		for (Balloon* balloon : normalBalloons)
		{
			if (balloon->Active())
				continue;

			return balloon->Spawn(spawnCoord, owner);
		}
	}
	else
	{
		for (TimerBalloon* balloon : timerBalloons)
		{
			if (balloon->Active())
				continue;

			return balloon->Spawn(spawnCoord, owner);
		}
	}

	return false;
}
