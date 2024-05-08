#pragma once

/* 
CONCRETE CLASS
Owned by DartManager 
*/
class Dart : public ColliderHolder
{
public:
	Dart();
	~Dart();

	void Init();

	void Update();
	void Render();

	void Debug();

public:

	/// <summary>
	/// Spawn dart
	/// </summary>
	/// <param name="spawnPos"> : ���� ���� ��ġ </param>
	/// <param name="fireDirection"> : �߻� ���� </param>
	void Spawn(const Vector2& spawnPos, const Direction& fireDirection);

public: /* Getters and setters */
	ColliderRect*	GetBody() const { return body; }

	bool			GetIsActive() const { return isActive; }
	void			SetActive(const bool& active) { this->isActive = active; }

private:

	/* Game map ���� ������ ���� dart ó�� */
	void HandleBoundary();

	/// <summary>
	/// Collision call back function
	/// </summary>
	/// <param name="targetCollider"> : Entered collider </param>
	/// <param name="owner"> : Owner of the entered collider </param>
	void OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner);

private:

	bool isActive{};

private:
	/* Body collider */
	ColliderRect* body{};

private:

	map<Direction, Object*> dirTexMap{}; // Dart ���⿡ ���� Texture map
	Object*					curTexObj{}; // ������ ������ ���� Texture object
	
private:

	Vector2		direction{};
	const float	SPEED = 2500.f;
};
