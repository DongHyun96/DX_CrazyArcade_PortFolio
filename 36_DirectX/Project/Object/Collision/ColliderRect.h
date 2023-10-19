#pragma once

enum ColliderTag
{
	DEFAULT,
	CHARACTER,
	CHARACTER_PUSH
};

class ColliderRect : public Collider // �ش� ��ü
{
public:

	ColliderRect(Vector2 size);
	~ColliderRect();

	void SetVertex() override;

	bool OBBCollision(const Vector2& point, ColliderHolder* owner = nullptr)	override;
	bool OBBCollision(ColliderRect* rect, ColliderHolder* owner = nullptr)		override;
	bool OBBCollision(ColliderCircle* other) override;

	// ���� : Always use Global Position for Collision detection
	bool AABBCollision(const Vector2& point, ColliderHolder* owner = nullptr);
	bool AABBCollision(ColliderRect* rect, ColliderHolder* owner = nullptr);


	Vector2 GlobalSize() const { return Vector2(size.x * globalScale.x, size.y * globalScale.y); } // Get global size

	// ���� : ȸ���� ���� ���� �簢�������� ���, Local �������� ��ȯ�� ��
	float	Left()		const { return translation.x - size.x * 0.5f; }
	float	Right()		const { return translation.x + size.x * 0.5f; }
	float	Top()		const { return translation.y + size.y * 0.5f; }
	float	Bottom()	const { return translation.y - size.y * 0.5f; }
	Vector2 LocalSize() const { return size; }

	void SetColliderTag(const ColliderTag& tag) { this->tag = tag; }
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
	
	void SetColliderRect(const Vector4& UDLR);

private:

	Vector2 size; // Local size

	set<ColliderHolder*> enteredPointOwners{};

	set<ColliderRect*> enteredBodies{};
	
	function<void(ColliderHolder*)> PointEnterEvent{};
	function<void(ColliderHolder*)> PointStayEvent{};
	function<void(ColliderHolder*)> PointExitEvent{};

	function<void(ColliderRect*, ColliderHolder*)> RectEnterEvent{};
	function<void(ColliderRect*, ColliderHolder*)> RectStayEvent{};
	function<void(ColliderRect*, ColliderHolder*)> RectExitEvent{};

	ColliderTag tag{DEFAULT};

};
