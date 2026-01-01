#pragma once

/* 
CONCRETE CLASS
획득하는 즉시 발동되는 아이템
*/
class ImmediateItem : public Item
{
public:
	ImmediateItem(const ItemName& itemName);
	~ImmediateItem();


	virtual bool UseItem(Character* itemUser) override;

private:

	virtual void OnColliderPointEnter(ColliderHolder* owner) override;

private:

	virtual void EarnedRenderHook() override;
	virtual void EarnedSetterHook() override;

};
