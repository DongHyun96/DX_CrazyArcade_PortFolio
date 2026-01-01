#include "Framework.h"
#include "ItemStrategy.h"

ItemStrategy::ItemStrategy() {}

RollerStrategy::RollerStrategy() {}
RollerStrategy::~RollerStrategy() {}

RedDevilStrategy::RedDevilStrategy() {}
RedDevilStrategy::~RedDevilStrategy() {}

FluidStrategy::FluidStrategy() {}
FluidStrategy::~FluidStrategy() {}

FluidUltraStrategy::FluidUltraStrategy() {}
FluidUltraStrategy::~FluidUltraStrategy() {}

BubbleStrategy::BubbleStrategy() {}
BubbleStrategy::~BubbleStrategy() {}

SpaceStrategy::SpaceStrategy() {}
SpaceStrategy::~SpaceStrategy() {}

OwlStrategy::OwlStrategy() {}
OwlStrategy::~OwlStrategy() {}

TurtleStrategy::TurtleStrategy() {}
TurtleStrategy::~TurtleStrategy() {}

NeedleStrategy::NeedleStrategy() {}
NeedleStrategy::~NeedleStrategy() {}

DartStrategy::DartStrategy() {}
DartStrategy::~DartStrategy() {}

TimerBalloonStrategy::TimerBalloonStrategy() {}
TimerBalloonStrategy::~TimerBalloonStrategy() {}


bool RollerStrategy::UseStrategy(Character* itemUser)
{
	return itemUser->IncreaseSpeed();
}


bool RedDevilStrategy::UseStrategy(Character* itemUser)
{
	return itemUser->IncreaseSpeed(true);
}

bool FluidStrategy::UseStrategy(Character* itemUser)
{
	return itemUser->IncreaseStreamLv();
}


bool FluidUltraStrategy::UseStrategy(Character* itemUser)
{
	return itemUser->IncreaseStreamLv(true);
}

bool BubbleStrategy::UseStrategy(Character* itemUser)
{
	return itemUser->AddLeftBalloonCnt();
}

bool SpaceStrategy::UseStrategy(Character* itemUser)
{
	if (itemUser->GetCharacterState() != C_IDLE) return false;

	itemUser->SetCharacterState(C_SPACECRAFT);

	return true;
}

bool OwlStrategy::UseStrategy(Character* itemUser)
{
	if (itemUser->GetCharacterState() != C_IDLE) return false;
	itemUser->SetCharacterState(C_OWL);

	return true;
}


bool TurtleStrategy::UseStrategy(Character* itemUser)
{
	if (itemUser->GetCharacterState() != C_IDLE) return false;

	itemUser->SetCharacterState(C_TURTLE);

	return true;
}


bool NeedleStrategy::UseStrategy(Character* itemUser)
{
	if (itemUser->GetCharacterState() != C_CAPTURED) return false;

	itemUser->SetCharacterState(C_RETURN_IDLE);

	return true;
}

bool DartStrategy::UseStrategy(Character* itemUser)
{
	switch (itemUser->GetCharacterState())
	{
	case C_IDLE: case C_SPACECRAFT: case C_OWL: case C_TURTLE:

		GM->GetDartManager()->Spawn(itemUser->GetBody()->translation, itemUser->GetCurFaceDir());

		return true;
	default:
		return false;
	}

	return false;
}

bool TimerBalloonStrategy::UseStrategy(Character* itemUser)
{
	switch (itemUser->GetCharacterState())
	{
	case C_IDLE: case C_SPACECRAFT: case C_OWL: case C_TURTLE:
	{
		Util::Coord deployCoord = GM->GetCollidedMapCellCoord(itemUser->GetBody()->GlobalPosition());
		
		if (GM->GetBalloonManager()->Spawn(deployCoord, itemUser, false))
		{
			SOUND->Play("BalloonDeploy", 1.f);
			return true;
		}
	}
	default:
		return false;
	}

	return false;
}
