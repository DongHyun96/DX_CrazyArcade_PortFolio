#include "Framework.h"
#include "ItemStrategy.h"

ItemStrategy::ItemStrategy()
{
}

RollerStrategy::RollerStrategy()
{
}

RollerStrategy::~RollerStrategy()
{
}

void RollerStrategy::UseStrategy(Character* itemUser)
{
	itemUser->IncreaseSpeed();
}

RedDeamonStrategy::RedDeamonStrategy()
{
}

RedDeamonStrategy::~RedDeamonStrategy()
{
}

