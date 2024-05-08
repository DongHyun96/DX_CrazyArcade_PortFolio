#pragma once


/* 
CONCRETE CLASS
�÷��� �� �ϳ� �� �Ҹ��Ͽ� ����� �� �ִ� ������(ex - Dart, TimerBalloon, �ٴ� ��)
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
	/* �Ҹ� �������� ���� ���� */
	UINT leftCnt{};

private:
	/* ���� ���� Text UI ��ġ */
	Vector2 leftCntTextPos{};

};
