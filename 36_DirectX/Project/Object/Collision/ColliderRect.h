#pragma once

enum ColliderTag
{
	DEFAULT,
	CHARACTER,
	CHARACTER_PUSH
};

class ColliderRect : public Collider // 해당 주체
{
public:

	ColliderRect(Vector2 size);
	~ColliderRect();

	void SetVertex() override;

	bool OBBCollision(const Vector2& point, Transform* owner = nullptr)		override;
	bool OBBCollision(ColliderRect* rect, Transform* owner = nullptr)		override;
	bool OBBCollision(ColliderCircle* other) override;

	// 주의 : Always use Global Position for Collision detection
	bool AABBCollision(const Vector2& point,	Transform* owner = nullptr);
	bool AABBCollision(ColliderRect* rect,		Transform* owner = nullptr);


	Vector2 GlobalSize() const { return Vector2(size.x * globalScale.x, size.y * globalScale.y); } // Get global size

	// 주의 : 회전이 들어가지 않은 사각형에서만 사용, Local 기준으로 반환할 것
	float	Left()		const { return translation.x - size.x * 0.5f; }
	float	Right()		const { return translation.x + size.x * 0.5f; }
	float	Top()		const { return translation.y + size.y * 0.5f; }
	float	Bottom()	const { return translation.y - size.y * 0.5f; }
	Vector2 LocalSize() const { return size; }

	void SetColliderTag(const ColliderTag& tag) { this->tag = tag; }
	ColliderTag GetColliderTag() const { return tag; }

public:

	void SetPointEnterEvent(function<void(Transform*)> E) { this->PointEnterEvent = E; }
	void SetPointStayEvent(function<void(Transform*)> E) { this->PointStayEvent = E; }
	void SetPointExitEvent(function<void(Transform*)> E) { this->PointExitEvent = E; }

	void SetRectEnterEvent(function<void(ColliderRect*, Transform*)> E) { this->RectEnterEvent = E; }
	void SetRectStayEvent(function<void(ColliderRect*, Transform*)> E) { this->RectStayEvent = E; }
	void SetRectExitEvent(function<void(ColliderRect*, Transform*)> E) { this->RectExitEvent = E; }

public:
	set<ColliderRect*>& EnteredBodies() { return enteredBodies; }

private:

	Vector2 size; // Local size

	set<Transform*> enteredPointOwners{};

	set<ColliderRect*> enteredBodies{};
	
	function<void(Transform*)> PointEnterEvent{};
	function<void(Transform*)> PointStayEvent{};
	function<void(Transform*)> PointExitEvent{};

	function<void(ColliderRect*, Transform*)> RectEnterEvent{};
	function<void(ColliderRect*, Transform*)> RectStayEvent{};
	function<void(ColliderRect*, Transform*)> RectExitEvent{};

	ColliderTag tag{DEFAULT};

};
