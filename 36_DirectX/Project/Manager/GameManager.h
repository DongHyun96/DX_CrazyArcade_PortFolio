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


private:

	Transform* gameFieldTransform{};

};
