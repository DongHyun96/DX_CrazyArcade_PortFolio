#pragma once

/* Collider 구분용 Tags */
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
	
public: /* Collision detection 관련 */

	bool OBBCollision(const Vector2& point, ColliderHolder* owner = nullptr)	override;
	bool OBBCollision(ColliderRect* rect, ColliderHolder* owner = nullptr)		override;
	bool OBBCollision(ColliderCircle* other) override;

	/* 주의 : Always use Global Position for Collision detection */
	bool AABBCollision(const Vector2& point, ColliderHolder* owner = nullptr);

	/* 주의 : Always use Global Position for Collision detection */
	bool AABBCollision(ColliderRect* rect, ColliderHolder* owner = nullptr);

public:

	Vector2 GlobalSize() const { return Vector2(size.x * globalScale.x, size.y * globalScale.y); }

	// 주의 : 회전이 들어가지 않은 사각형(AABB Rect)에서만 사용, Local 기준으로 반환할 것
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
	/// Up, down, left, right값으로 setting
	/// </summary>
	/// <param name="UDLR"> : Each up, down, left, right values </param>
	void SetColliderRect(const Vector4& UDLR);

/***************************************************************************************************
*                                          Member variables                                        *
****************************************************************************************************/

private:

	Vector2 size; // Local size

private:

	set<ColliderHolder*>	enteredPointOwners{};	// 현재 이 ColliderRect에 들어와 있는 모든 pointer들의 Owner set
	set<ColliderRect*>		enteredBodies{};		// 현재 이 ColliderRect에 들어와 있는 모든 Other collider rects

private: /* Call back events */
	
	function<void(ColliderHolder*)> PointEnterEvent{};	// 점(특정 GameObject의 position)이 들어왔을 때의 call back function pointer (Event)
	function<void(ColliderHolder*)> PointStayEvent{};	// 점이 stay하고 있을 때의 call back function pointer
	function<void(ColliderHolder*)> PointExitEvent{};	// 점이 나갔을 때의 call back function pointer

	function<void(ColliderRect*, ColliderHolder*)> RectEnterEvent{};	// 다른 ColliderRect가 들어왔을 때의 call back function pointer
	function<void(ColliderRect*, ColliderHolder*)> RectStayEvent{};		// 다른 ColliderRect가 stay하고 있을 때의 call back function pointer
	function<void(ColliderRect*, ColliderHolder*)> RectExitEvent{};		// 다른 ColliderRect가 나갔을 때의 call back function pointer

private:
	ColliderTag tag{DEFAULT};	// Collider 구분을 위한 collider tag
};
