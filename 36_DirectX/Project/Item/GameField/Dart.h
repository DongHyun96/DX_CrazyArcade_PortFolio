#pragma once

// 충돌처리해야 할 물체 : 물풍선 / hidable이 아닌 블록들 / 경계선

class Dart : public ColliderHolder
{
public:
	Dart();
	~Dart();

	void Update();
	void Render();

	void Debug();

public:

	void Spawn(const Vector2& spawnPos, const Direction& fireDirection);

	ColliderRect* GetBody() const { return body; }

	bool GetIsActive() const { return isActive; }
	void SetActive(const bool& active) { this->isActive = active; }

private:

	void HandleBoundary();

	void OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner);

private:

	bool isActive{};

	map<Direction, Object*> dirTexMap{};

	Object* curTexObj{};

	ColliderRect*	body{};
	
	Vector2 direction{};

	const float SPEED = 2500.f;

};
