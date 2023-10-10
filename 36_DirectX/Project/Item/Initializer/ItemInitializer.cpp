#include "Framework.h"
#include "ItemInitializer.h"


ItemInitializer::ItemInitializer()
{
}

ItemInitializer::~ItemInitializer()
{
}

void ItemInitializer::CreateCommonFields(const ItemName& itemName, Object** texObj, ItemStrategy** itemStrategy)
{
	switch (itemName)
	{
	case ROLLER:
		*texObj			= new Object(CELL_WORLD_SIZE, L"InGame/Item/Roller.png");
		*itemStrategy	= new RollerStrategy;
		break;
	case RED_DEVIL:
		*texObj			= new Object(CELL_WORLD_SIZE, L"InGame/Item/Devil.png");
		*itemStrategy	= new RedDevilStrategy;
		break;
	case FLUID:
		*texObj			= new Object(CELL_WORLD_SIZE, L"InGame/Item/Potion2.png");
		*itemStrategy	= new FluidStrategy;
		break;
	case FLUID_ULTRA:
		*texObj			= new Object({ CELL_WORLD_SIZE.x * 1.2f, CELL_WORLD_SIZE.y * 1.2f}, L"InGame/Item/Gas.png");
		*itemStrategy	= new FluidUltraStrategy;
		break;
	case BUBBLE:
		*texObj			= new Object(CELL_WORLD_SIZE, L"InGame/Item/balloon2.png");
		*itemStrategy	= new BubbleStrategy;
		break;
	case NEEDLE:
		*texObj			= new Object(CELL_WORLD_SIZE, L"InGame/Item/Needle.png");
		*itemStrategy	= new NeedleStrategy;
		break;
	default:
		*texObj			= nullptr;
		*itemStrategy	= nullptr;
		break;
	}
}

