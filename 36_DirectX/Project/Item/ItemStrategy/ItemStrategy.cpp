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