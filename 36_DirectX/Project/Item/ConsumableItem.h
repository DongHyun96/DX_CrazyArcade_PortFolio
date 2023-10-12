#pragma once


//enum ItemState
//{
//	HIDE,		// 아직 block 뒤에 있을 때
//	SPAWNED,	// 게임 필드 위에 spawn된 상태
//	EARNED,		// 플레이어가 먹었을 떄 상태
//	RESPAWN		// 캐릭터가 죽었을 때 먹은 아이템이 반환될 때 사용
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
