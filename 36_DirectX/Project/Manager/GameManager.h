#pragma once

class Transform;
class Character;

class GameManager
{
private:

	GameManager();
	~GameManager();

public:
	
	static GameManager* GetInst()
	{
		static GameManager singleton;
		return &singleton;
	}

	void Update();
	
	void SetPlayer(Character* player) { this->player = player; }
	Character* GetPlayer() const { return player; }

public:

	Transform* GetGameFieldTransform() const { return gameFieldTransform; }
	bool IsEditMode() const { return editMode; }

	float GetMapL() const { return mapL; }
	float GetMapR() const { return mapR;}
	float GetMapT() const { return mapT; }
	float GetMapB() const { return mapB; }

private:

	Character* player{};

	Transform* gameFieldTransform{};
	
	bool editMode = false;

	float mapL{};
	float mapR{};
	float mapT{};
	float mapB{};

};
