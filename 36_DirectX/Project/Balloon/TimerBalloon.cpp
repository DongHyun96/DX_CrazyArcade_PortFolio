#include "Framework.h"
#include "TimerBalloon.h"


TimerBalloon::TimerBalloon(Animation* animation)
	:Balloon(animation)
{
}

TimerBalloon::~TimerBalloon()
{
}

bool TimerBalloon::Spawn(const Util::Coord& spawnCoord, Character* owner)
{
	if (Balloon::Spawn(Util::ConvertBoardIdxToWorldPos(spawnCoord)))
	{
		this->spawnCoord = spawnCoord;
		this->streamLv = owner->GetStreamLv();
		this->owner = owner;

		owner->AddTimerBalloon(this);

		return true;
	}

	return false;
}

void TimerBalloon::Explode()
{
	isActive = false;

	for (auto it = activeBalloonPositions.begin(); it != activeBalloonPositions.end(); it++)
	{
		if (*it == body->translation)
		{
			activeBalloonPositions.erase(it);
			break;
		}
	}

	body->EnteredBodies().clear();

	GM->GetStreamManager()->SpawnStream(spawnCoord, streamLv);

	owner = nullptr;

	if (!explodeSoundPlayed)
	{
		SOUND->Play("BalloonExplode", 1.f);
		explodeSoundPlayed = true;
	}
}


void TimerBalloon::HandleExplode()
{
	// 부모클래스에서는 ExplodeTimer가 있는데 여기서는 Timer의 영향을 받지 않도록 그냥 놔둘것임
}
