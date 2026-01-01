#pragma once


/* 
CONCRETE CLASS
플레이 중 하나 씩 소모하여 사용할 수 있는 아이템(ex - Dart, TimerBalloon, 바늘 등)
*/
class ConsumableItem : public Item
{
public:
	ConsumableItem(const ItemName& itemName);
	~ConsumableItem();

	virtual bool UseItem(Character* itemUser) override;

private:

	virtual void OnColliderPointEnter(ColliderHolder* owner) override;

private:

	virtual void EarnedRenderHook() override;
	virtual void EarnedSetterHook() override;

private:
	/* 소모 아이템의 남은 갯수 */
	UINT leftCnt{};

private:
	/* 남은 갯수 Text UI 위치 */
	Vector2 leftCntTextPos{};

};
