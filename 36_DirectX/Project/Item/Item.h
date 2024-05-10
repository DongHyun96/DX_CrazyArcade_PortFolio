#pragma once


// ImmediateItem  (power-ups, Ridable)
// ConsumableItem (�ϵ�, ������, Ÿ�̸� ��ź, ��Ʈ ��)

/* �������� ���� */
enum ItemState
{
	HIDDEN,		// ���� block �ڿ� ���� ��
	SPAWNED,	// ���� �ʵ� ���� spawn�� ����
	EARNED,		// �÷��̾ �Ծ��� �� ����
	// ĳ���Ͱ� �׾��� �� ���� �������� ���Ӹʿ� ��ȯ�� �� ��� (������ RESPAWN�� �־���)
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
	/// ������ ȿ�� ����ϱ�
	/// </summary>
	/// <param name="itemUser"> : �������� ����ϴ� ĳ���� </param>
	/// <returns> : ������ ȿ���� �ߵ��Ǿ��ٸ� return true </returns>
	virtual bool UseItem(Character* itemUser);

public: /* Getters and setters */

	ColliderRect*	GetBody() const { return body; }
	ItemState		GetItemState() const { return itemState; }

	bool			GetIsActive() const { return isActive; }

	void			SetActive(const bool& isActive) { this->isActive = isActive; }

	static void		SetSpawnSoundPlayed(const bool& played) { spawnSoundPlayed = played; }

public:
	
	/// <summary>
	/// ���� ��Ű��
	/// </summary>
	/// <param name="spawnPos"> : Spawn position </param>
	void Spawn(const Vector2& spawnPos);

	/// <summary>
	/// Ư�� ĳ���Ͱ� �׾��� ��, �ش� ĳ���Ͱ� ȹ���ߴ� ������ ������ ��Ű�� | Not implemented
	/// </summary>
	/// <param name="src"> : ������ ������(ĳ���Ͱ� ���� ��ġ)</param>
	/// <param name="dst"> : ������ ���� </param>
	void Respawn(const Vector2& src, const Vector2& dst);

protected:

	/// <summary>
	/// State �ٲ��� ���������� ���� | EARNED�� setting�Ǵ� ��� �ڽ�Ŭ�������� ���� �ٸ��� ó���ϴ� Hook Method�� �ɾ��
	/// </summary>
	/// <param name="itemState"> : Next itemState </param>
	void SetItemState(const ItemState& itemState); 

protected:

	/// <summary>
	/// ĳ���Ϳ� �浹���� �� �̿�
	/// </summary>
	/// <param name="owner"> : Point(position) owner </param>
	virtual void OnColliderPointEnter(ColliderHolder* owner) = 0;

protected:

	/* 
	Render()�Լ� ���� itemState�� EARNED ������ ���� Template hook method
	itemState�� EARNED ������ �� Immediate item�� Consumable item�� RenderHook �κ��� �����ΰ� �ٸ�
	*/
	virtual void EarnedRenderHook() = 0;

	/*
	SetItemState �Լ� ���� Template hook method
	Setter�� setting�� EARNED state�� setting�� �� ó���κ��� �ڽĿ� ���� �ٸ�
	*/
	virtual void EarnedSetterHook() = 0;

private:

	/// <summary>
	/// Collision call back function, ���ٱ� ��� �浹���� �� �̵�
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
	Object*			texObj{};		// Body�� transform�� ����

	bool			isActive{};

private:

	ItemStrategy* itemStrategy{};	// This item's strategy

private:

	ItemState itemState = HIDDEN;

private: /* ������ ������ floating effect ���� */

	float		floatingTime{};
	float		floatingYSpeed			= 25.f;
	const float FLOATING_Y_UPDATE_TICK	= 1.f;

private:
	/*
	Update �� tick�� ���ÿ� �������� �Ծ��� ��, ������ ȹ�� ���� ����Ʈ�� ������ �ʹ� ŭ
	������ ȹ�� sfx�� Update tick ������ �� ���� ó���� �� ����
	*/
	static bool spawnSoundPlayed;
};
