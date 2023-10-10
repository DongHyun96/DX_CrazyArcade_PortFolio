#pragma once
class ImmediateItem : public Item
{
public:
	ImmediateItem(const ItemName& itemName);
	~ImmediateItem();


	virtual bool UseItem(Character* itemUser) override;

private:


	virtual void OnColliderPointEnter(ColliderHolder* owner) override;
	virtual void EarnedRenderHook() override;
	virtual void EarnedSetterHook() override;



};
