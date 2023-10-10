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

bool NeedleStrategy::UseStrategy(Character* itemUser)
{
	if (itemUser->GetCharacterState() != C_CAPTURED) return false;

	itemUser->SetCharacterState(C_RETURN_IDLE);
}