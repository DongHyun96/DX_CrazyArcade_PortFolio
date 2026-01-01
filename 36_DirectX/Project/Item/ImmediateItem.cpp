#include "Framework.h"
#include "ImmediateItem.h"


ImmediateItem::ImmediateItem(const ItemName& itemName)
	:Item(itemName)
{
}

ImmediateItem::~ImmediateItem()
{
}


bool ImmediateItem::UseItem(Character* itemUser)
{
	return Item::UseItem(itemUser);
}


void ImmediateItem::OnColliderPointEnter(ColliderHolder* owner)
{
	if (!isActive) return;

	Character* character = dynamic_cast<Character*>(owner);

	if (character)
	{

		switch (character->GetCharacterState()) 
		{ 
		case C_SPACECRAFT: case C_CAPTURED: return;
		}

		UseItem(character); // Immediate use
		SetItemState(EARNED);
		SOUND->Play("ItemEarned", 0.5f);
		return;
	}
}

void ImmediateItem::EarnedRenderHook() {}

void ImmediateItem::EarnedSetterHook()
{
	isActive = false;
}

