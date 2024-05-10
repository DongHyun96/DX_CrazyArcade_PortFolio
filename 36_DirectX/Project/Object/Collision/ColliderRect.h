#pragma once

/* Collider ���п� Tags */
enum ColliderTag
{
	DEFAULT,
	CHARACTER,
	CHARACTER_PUSH
};

/* CONCRETE CLASS */
class ColliderRect : public Collider
{
public:

	ColliderRect(Vector2 size);
	~ColliderRect();

public:

	void SetVertex() override;
	
public: /* Collision detection ���� */

	bool OBBCollision(const Vector2& point, ColliderHolder* owner = nullptr)	override;
	bool OBBCollision(ColliderRect* rect, ColliderHolder* owner = nullptr)		override;
	bool OBBCollision(ColliderCircle* other) override;

	/* ���� : Always use Global Position for Collision detection */
	bool AABBCollision(const Vector2& point, ColliderHolder* owner = nullptr);

	/* ���� : Always use Global Position for Collision detection */
	bool AABBCollision(ColliderRect* rect, ColliderHolder* owner = nullptr);

public:

	Vector2 GlobalSize() const { return Vector2(size.x * globalScale.x, size.y * globalScale.y); }

	// ���� : ȸ���� ���� ���� �簢��(AABB Rect)������ ���, Local �������� ��ȯ�� ��
	float	Left()		const { return translation.x - size.x * 0.5f; }
	float	Right()		const { return translation.x + size.x * 0.5f; }
	float	Top()		const { return translation.y + size.y * 0.5f; }
	float	Bottom()	const { return translation.y - size.y * 0.5f; }
	Vector2 LocalSize() const { return size; }

public:

	void		SetColliderTag(const ColliderTag& tag) { this->tag = tag; }
	ColliderTag GetColliderTag() const { return tag; }

public:

	void SetPointEnterEvent(function<void(ColliderHolder*)> E) { this->PointEnterEvent = E; }
	void SetPointStayEvent(function<void(ColliderHolder*)> E) { this->PointStayEvent = E; }
	void SetPointExitEvent(function<void(ColliderHolder*)> E) { this->PointExitEvent = E; }

	void SetRectEnterEvent(function<void(ColliderRect*, ColliderHolder*)> E) { this->RectEnterEvent = E; }
	void SetRectStayEvent(function<void(ColliderRect*, ColliderHolder*)> E) { this->RectStayEvent = E; }
	void SetRectExitEvent(function<void(ColliderRect*, ColliderHolder*)> E) { this->RectExitEvent = E; }

public:
	set<ColliderHolder*>& EnteredPointOwners() { return enteredPointOwners; }
	set<ColliderRect*>& EnteredBodies() { return enteredBodies; }

public:
	
	/// <summary>
	/// Up, down, left, right������ setting
	/// </summary>
	/// <param name="UDLR"> : Each up, down, left, right values </param>
	void SetColliderRect(const Vector4& UDLR);

/***************************************************************************************************
*                                          Member variables                                        *
****************************************************************************************************/

private:

	Vector2 size; // Local size

private:

	set<ColliderHolder*>	enteredPointOwners{};	// ���� �� ColliderRect�� ���� �ִ� ��� pointer���� Owner set
	set<ColliderRect*>		enteredBodies{};		// ���� �� ColliderRect�� ���� �ִ� ��� Other collider rects

private: /* Call back events */
	
	function<void(ColliderHolder*)> PointEnterEvent{};	// ��(Ư�� GameObject�� position)�� ������ ���� call back function pointer (Event)
	function<void(ColliderHolder*)> PointStayEvent{};	// ���� stay�ϰ� ���� ���� call back function pointer
	function<void(ColliderHolder*)> PointExitEvent{};	// ���� ������ ���� call back function pointer

	function<void(ColliderRect*, ColliderHolder*)> RectEnterEvent{};	// �ٸ� ColliderRect�� ������ ���� call back function pointer
	function<void(ColliderRect*, ColliderHolder*)> RectStayEvent{};		// �ٸ� ColliderRect�� stay�ϰ� ���� ���� call back function pointer
	function<void(ColliderRect*, ColliderHolder*)> RectExitEvent{};		// �ٸ� ColliderRect�� ������ ���� call back function pointer

private:
	ColliderTag tag{DEFAULT};	// Collider ������ ���� collider tag
};
