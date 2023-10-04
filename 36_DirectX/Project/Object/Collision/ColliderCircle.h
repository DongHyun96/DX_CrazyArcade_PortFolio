#pragma once
class ColliderCircle : public Collider
{
public:
	ColliderCircle(float radius);
	~ColliderCircle();

	virtual void SetVertex() override;

	virtual bool Collision(Vector2 point, Transform* owner = nullptr) override;
	virtual bool Collision(ColliderRect* other, Transform* owner = nullptr) override;
	virtual bool Collision(ColliderCircle* other) override;

	float Radius() const { return radius * max(globalScale.x, globalScale.y); }

private:

	float radius{};

	const UINT VERTEX_COUNT = 36;
};
