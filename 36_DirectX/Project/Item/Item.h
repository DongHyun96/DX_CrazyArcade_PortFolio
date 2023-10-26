#pragma once

/*
TODO - 아이템 사용 전략 패턴 만들기
*/

// ImmediateItem (power-ups, Ridable)
// ConsumableItem (니들, 점프팩, 타이머 폭탄, 다트 등)

enum ItemState
{
	HIDE,		// 아직 block 뒤에 있을 때
	SPAWNED,	// 게임 필드 위에 spawn된 상태
	EARNED,		// 플레이어가 먹었을 떄 상태
	// 캐릭터가 죽었을 때 먹은 아이템이 반환될 때 사용 (원래는 RESPAWN이 있었음)
};

enum ItemName	// 전체 아이템 스폰률(블록 당 1/3)
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

	// TODO : 상황에 맞게끔 자식 클래스에서 Update Render 추가 처리할 것임
	void Update(); 
	void Render(); // EARNED의 경우 자식클래스에서 다르게 처리 -> Hook Method

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
	
	// State 바뀔때의 시작점으로 동작
	void SetItemState(const ItemState& itemState); // EARNED의 경우 자식클래스에서 서로 다르게 처리 -> Hook Method

protected:

	virtual void OnColliderPointEnter(ColliderHolder* owner) = 0; // 캐릭터와 충돌했을 때 이용

	virtual void EarnedUpdateHook() = 0;
	virtual void EarnedRenderHook() = 0;
	virtual void EarnedSetterHook() = 0;

private:
	void OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner); // 물줄기 등과 충돌했을 때 이용

protected:

	ItemName		itemName{};

	ColliderRect*	body{};
	Object*			texObj{}; // Body의 transform을 따라감

	ItemStrategy* itemStrategy{};
	
	bool isActive{};

private:

	ItemState itemState{ HIDE }; // c# 프로퍼티처럼 setter만 자식 클래스에서 사용하도록 할 것임

	float spawned_timeChecker{};
	float spawned_ySpeed{ 25.f };
	const float SPAWNED_Y_UPDATE_TICK = 1.f;

private:
	static bool spawnSoundPlayed;
};
