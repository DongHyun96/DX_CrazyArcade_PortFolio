#pragma once

class UIManager
{
private:
	UIManager();
	~UIManager();

public:

	static UIManager* GetInst()
	{
		static UIManager singleton;
		return &singleton;
	}

public:
	
	void Update();
	void Render();

private:

	void Debug();

private:
	
	Object* mainUI{};
	
	Object* itemUI{};

};
