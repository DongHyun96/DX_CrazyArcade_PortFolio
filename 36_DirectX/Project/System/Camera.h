#pragma once
class Camera : public Singleton<Camera>
{
public:
	Camera();
	~Camera();

	void Update();
	void Set();

	void FreeMode();
	void TargetMode();

	void SetTarget(Transform* target) { this->target = target; }

private:
	Transform*		transform{};
	MatrixBuffer*	viewBuffer;

	Transform*		target{};

	float speed{ 100.f };

	Vector2 offset{WIN_CENTER};
};
