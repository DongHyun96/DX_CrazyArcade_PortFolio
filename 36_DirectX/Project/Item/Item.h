#pragma once


// ImmediateItem  (power-ups, Ridable)
// ConsumableItem (니들, 점프팩, 타이머 폭탄, 다트 등)

/* 아이템의 상태 */
enum ItemState
{
	HIDDEN,		// 아직 block 뒤에 있을 때
	SPAWNED,	// 게임 필드 위에 spawn된 상태
	EARNED,		// 플레이어가 먹었을 떄 상태
	// 캐릭터가 죽었을 때 먹은 아이템이 게임맵에 반환될 때 사용 (원래는 RESPAWN이 있었음)
};

/* All item types(or names) */
enum ItemName	
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


/* ABSTRACT CLASS */
class Item : public ColliderHolder
{
public:
	Item(const ItemName& itemName);
	virtual ~Item();

	void Update(); 
	void Render(); 

	/// <summary>
	/// 아이템 효과 사용하기
	/// </summary>
	/// <param name="itemUser"> : 아이템을 사용하는 캐릭터 </param>
	/// <returns> : 아이템 효과가 발동되었다면 return true </returns>
	virtual bool UseItem(Character* itemUser);

public: /* Getters and setters */

	ColliderRect*	GetBody() const { return body; }
	ItemState		GetItemState() const { return itemState; }

	bool			GetIsActive() const { return isActive; }

	void			SetActive(const bool& isActive) { this->isActive = isActive; }

	static void		SetSpawnSoundPlayed(const bool& played) { spawnSoundPlayed = played; }

public:
	
	/// <summary>
	/// 스폰 시키기
	/// </summary>
	/// <param name="spawnPos"> : Spawn position </param>
	void Spawn(const Vector2& spawnPos);

	/// <summary>
	/// 특정 캐릭터가 죽었을 때, 해당 캐릭터가 획득했던 아이템 리스폰 시키기 | Not implemented
	/// </summary>
	/// <param name="src"> : 리스폰 시작점(캐릭터가 죽은 위치)</param>
	/// <param name="dst"> : 리스폰 끝점 </param>
	void Respawn(const Vector2& src, const Vector2& dst);

protected:

	/// <summary>
	/// State 바뀔때의 시작점으로 동작 | EARNED로 setting되는 경우 자식클래스에서 서로 다르게 처리하는 Hook Method를 걸어둠
	/// </summary>
	/// <param name="itemState"> : Next itemState </param>
	void SetItemState(const ItemState& itemState); 

protected:

	/// <summary>
	/// 캐릭터와 충돌했을 때 이용
	/// </summary>
	/// <param name="owner"> : Point(position) owner </param>
	virtual void OnColliderPointEnter(ColliderHolder* owner) = 0;

protected:

	/* 
	Render()함수 내의 itemState가 EARNED 상태일 때의 Template hook method
	itemState가 EARNED 상태일 때 Immediate item과 Consumable item의 RenderHook 부분의 구현부가 다름
	*/
	virtual void EarnedRenderHook() = 0;

	/*
	SetItemState 함수 내의 Template hook method
	Setter로 setting시 EARNED state로 setting할 때 처리부분이 자식에 따라 다름
	*/
	virtual void EarnedSetterHook() = 0;

private:

	/// <summary>
	/// Collision call back function, 물줄기 등과 충돌했을 때 이동
	/// </summary>
	/// <param name="targetCollider"> : Entered collider </param>
	/// <param name="owner"> : Entered collider owner </param>
	void OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner);

/***************************************************************************************************
*                                          Member variables                                        *
****************************************************************************************************/

protected:

	ItemName itemName{};

protected:

	ColliderRect*	body{};			// Body collider
	Object*			texObj{};		// Body의 transform을 따라감

	bool			isActive{};

private:

	ItemStrategy* itemStrategy{};	// This item's strategy

private:

	ItemState itemState = HIDDEN;

private: /* 스폰된 아이템 floating effect 관련 */

	float		floatingTime{};
	float		floatingYSpeed			= 25.f;
	const float FLOATING_Y_UPDATE_TICK	= 1.f;

private:
	/*
	Update 한 tick에 동시에 아이템을 먹었을 때, 아이템 획득 사운드 이펙트의 볼륨이 너무 큼
	아이템 획득 sfx는 Update tick 내에서 한 번만 처리를 할 예정
	*/
	static bool spawnSoundPlayed;
};
