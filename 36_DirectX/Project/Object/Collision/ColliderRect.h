#pragma once


class ColliderRect : public Collider // 해당 주체
{
public:

	ColliderRect(Vector2 size);
	~ColliderRect();

	void SetVertex() override;

	bool Collision(Vector2 point, Transform* owner = nullptr)			override;
	bool Collision(ColliderRect* rect, Transform* owner = nullptr)		override;
	bool Collision(ColliderCircle* other) override;

	Vector2 GlobalSize() const { return Vector2(size.x * globalScale.x, size.y * globalScale.y); } // Get global size

	// 주의 : 회전이 들어가지 않은 사각형에서만 사용, Local 기준으로 반환할 것
	float	Left()		const { return translation.x - size.x * 0.5f; }
	float	Right()		const { return translation.x + size.x * 0.5f; }
	float	Top()		const { return translation.y + size.y * 0.5f; }
	float	Bottom()	const { return translation.y - size.y * 0.5f; }
	Vector2 LocalSize() const { return size; }

public:

	void SetPointEnterEvent(function<void(Transform*)> E) { this->PointEnterEvent = E; }
	void SetPointExitEvent(function<void(Transform*)> E) { this->PointExitEvent = E; }
	void SetRectEnterEvent(function<void(Transform*)> E) { this->RectEnterEvent = E; }
	void SetRectExitEvent(function<void(Transform*)> E) { this->RectExitEvent = E; }

private:

	Vector2 size; // Local size

	set<Transform*> enteredPointOwners{};
	set<Transform*> enteredRectOwners{};
	
	function<void(Transform*)> PointEnterEvent{};
	function<void(Transform*)> PointExitEvent{};

	function<void(Transform*)> RectEnterEvent{};
	function<void(Transform*)> RectExitEvent{};

};
