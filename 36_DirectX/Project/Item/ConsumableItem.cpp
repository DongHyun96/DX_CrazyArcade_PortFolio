#include "Framework.h"
#include "ConsumableItem.h"


ConsumableItem::ConsumableItem(const ItemName& itemName)
	:Item(itemName)
{
}

ConsumableItem::~ConsumableItem()
{
}

bool ConsumableItem::UseItem(Character* itemUser)
{
	if (Item::UseItem(itemUser))
	{
		leftCnt--;

		if (leftCnt <= 0)
		{
			isActive = false;
			itemUser->SetConsumableItem(nullptr);
		}

		return true;
	}

	return false;
}

// 아이템을 먹었을 때의 처리
void ConsumableItem::OnColliderPointEnter(ColliderHolder* owner)
{
	if (!isActive) return;

	Character* character = dynamic_cast<Character*>(owner);

	if (character)
	{
		switch (character->GetCharacterState())
		{
		case C_SPACECRAFT: case C_CAPTURED: return;
		}

		SetItemState(EARNED);

		SOUND->Play("ItemEarned", 0.5f);

		// 만약 해당 캐릭터가 다른 ConsumableItem을 들고 있을 때, 이전 아이템의 active를 꺼줌
		if (character->GetConsumableItem())
			character->GetConsumableItem()->SetActive(false);

		// set this item to character
		character->SetConsumableItem(this);

		// 1p인지 2p인지 enemy인지에 따라서도 달라짐 (잡히는 위치가)
		switch (character->GetPlayerType())
		{
		case P1:
			body->translation = { 1655, 175 };
			// 1694 157
			leftCntTextPos = { 1694, 157 };

			break;
		case P2:
			break;
		default:
			break;
		}
		return;
	}
}

void ConsumableItem::EarnedUpdateHook()
{
	// body와 texture는 부모 클래스에서 렌더링 되고(위치가 잡힌채로), 남은 아이템 수 폰트를 띄워야 함
}

void ConsumableItem::EarnedRenderHook()
{
	// body와 texture는 부모 클래스에서 렌더링 되고(위치가 잡힌채로), 남은 아이템 수 폰트를 띄워야 함
	FONT->RenderText(L"x " + to_wstring(leftCnt), "BazziFontBold", Util::ConvertDxPosToAPIPos(leftCntTextPos));
}

void ConsumableItem::EarnedSetterHook()
{
	body->SetParent(nullptr);
	body->scale = { 0.7f, 0.7f };

	leftCnt = (itemName == NEEDLE) ? 1 : 3;
}

