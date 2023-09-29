#pragma once
class Knight : public Character
{
public:
	enum State
	{
		IDLE,
		WALK,
		ATTACK,
	};

public:

	Knight();
	~Knight();

	void Update() override;
	void Render();

	void EndAttack();

	void Save();
	void Load();


private:
	virtual void AddAction() override;

	Collider* weaponCollider{};

};
