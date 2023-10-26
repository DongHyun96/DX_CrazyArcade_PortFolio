#pragma once

/*
TODO - ������ ��� ���� ���� �����
*/

// ImmediateItem (power-ups, Ridable)
// ConsumableItem (�ϵ�, ������, Ÿ�̸� ��ź, ��Ʈ ��)

enum ItemState
{
	HIDE,		// ���� block �ڿ� ���� ��
	SPAWNED,	// ���� �ʵ� ���� spawn�� ����
	EARNED,		// �÷��̾ �Ծ��� �� ����
	// ĳ���Ͱ� �׾��� �� ���� �������� ��ȯ�� �� ��� (������ RESPAWN�� �־���)
};

enum ItemName	// ��ü ������ ������(��� �� 1/3)
{
	ROLLER,		
	BUBBLE,
	FLUID,
	FLUID_ULTRA,
	RED_DEVIL,

	I_SPACECRAFT, // 5
	I_OWL,
	I_TURTLE,

	NEEDLE, // 8
	DART,
	TIMER_BALLOON
};


// Abstract
class Item : public ColliderHolder
{
public:
	Item(const ItemName& itemName);
	virtual ~Item();

	// TODO : ��Ȳ�� �°Բ� �ڽ� Ŭ�������� Update Render �߰� ó���� ����
	void Update(); 
	void Render(); // EARNED�� ��� �ڽ�Ŭ�������� �ٸ��� ó�� -> Hook Method

	virtual bool UseItem(Character* itemUser);

public:

	ColliderRect*	GetBody()		const { return body; }
	ItemState		GetItemState()	const { return itemState; }

	bool			GetIsActive()	const { return isActive; }

	void			SetActive(const bool& isActive) { this->isActive = isActive; }
	
	void Spawn(const Vector2& spawnPos);
	void Respawn(const Vector2& src, const Vector2& dst);

	static void SetSpawnSoundPlayed(const bool& played) { spawnSoundPlayed = played; }


protected:
	
	// State �ٲ��� ���������� ����
	void SetItemState(const ItemState& itemState); // EARNED�� ��� �ڽ�Ŭ�������� ���� �ٸ��� ó�� -> Hook Method

protected:

	virtual void OnColliderPointEnter(ColliderHolder* owner) = 0; // ĳ���Ϳ� �浹���� �� �̿�

	virtual void EarnedUpdateHook() = 0;
	virtual void EarnedRenderHook() = 0;
	virtual void EarnedSetterHook() = 0;

private:
	void OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner); // ���ٱ� ��� �浹���� �� �̿�

protected:

	ItemName		itemName{};

	ColliderRect*	body{};
	Object*			texObj{}; // Body�� transform�� ����

	ItemStrategy* itemStrategy{};
	
	bool isActive{};

private:

	ItemState itemState{ HIDE }; // c# ������Ƽó�� setter�� �ڽ� Ŭ�������� ����ϵ��� �� ����

	float spawned_timeChecker{};
	float spawned_ySpeed{ 25.f };
	const float SPAWNED_Y_UPDATE_TICK = 1.f;

private:
	static bool spawnSoundPlayed;
};
