#pragma once

class Transform;

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

public:

	Transform* GetGameFieldTransform() const { return gameFieldTransform; }
	bool IsEditMode() const { return editMode; }

private:

	Transform* gameFieldTransform{};
	
	bool editMode = false;
};
