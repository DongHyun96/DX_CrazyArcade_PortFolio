#pragma once

// 각 블록들이 랜덤하게 생성한 아이템들을 모두 들고 있을 것임
class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	void Update();
	void Render();

	void Init();

	static vector<Item*>& GetItems() { return items; }
	
	static void AddItem(Item* item); // 각 블록에서 아이템을 생성했다면 ItemManager에 넣어둠

private:
	void HandleCollisions();

private:
	
	static vector<Item*> items;
};
