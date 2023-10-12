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

// �������� �Ծ��� ���� ó��
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

		// ���� �ش� ĳ���Ͱ� �ٸ� ConsumableItem�� ��� ���� ��, ���� �������� active�� ����
		if (character->GetConsumableItem())
			character->GetConsumableItem()->SetActive(false);

		// set this item to character
		character->SetConsumableItem(this);

		// 1p���� 2p���� enemy������ ���󼭵� �޶��� (������ ��ġ��)
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
	// body�� texture�� �θ� Ŭ�������� ������ �ǰ�(��ġ�� ����ä��), ���� ������ �� ��Ʈ�� ����� ��
}

void ConsumableItem::EarnedRenderHook()
{
	// body�� texture�� �θ� Ŭ�������� ������ �ǰ�(��ġ�� ����ä��), ���� ������ �� ��Ʈ�� ����� ��
	FONT->RenderText(L"x " + to_wstring(leftCnt), "BazziFontBold", Util::ConvertDxPosToAPIPos(leftCntTextPos));
}

void ConsumableItem::EarnedSetterHook()
{
	body->SetParent(nullptr);
	body->scale = { 0.7f, 0.7f };

	leftCnt = (itemName == NEEDLE) ? 1 : 3;
}

