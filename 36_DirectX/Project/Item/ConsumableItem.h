#pragma once


//enum ItemState
//{
//	HIDE,		// ���� block �ڿ� ���� ��
//	SPAWNED,	// ���� �ʵ� ���� spawn�� ����
//	EARNED,		// �÷��̾ �Ծ��� �� ����
//	RESPAWN		// ĳ���Ͱ� �׾��� �� ���� �������� ��ȯ�� �� ���
//};
//

class ConsumableItem : public Item
{
public:
	ConsumableItem(const ItemName& itemName);
	~ConsumableItem();

	virtual bool UseItem(Character* itemUser) override;

private:

	virtual void OnColliderPointEnter(ColliderHolder* owner) override;

	virtual void EarnedUpdateHook() override;
	virtual void EarnedRenderHook() override;
	virtual void EarnedSetterHook() override;

private:
	
	UINT leftCnt{};

private:

	Vector2 leftCntTextPos{};

};
