#pragma once

// 각 블록들이 랜덤하게 생성한 아이템들을 모두 들고 있을 것임
class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	void Update();
	void Render();

	static vector<Item*>& GetItems() { return items; }
	
	static void AddItem(Item* item);

private:
	void HandleCollisions();

private:
	
	static vector<Item*> items;
};
