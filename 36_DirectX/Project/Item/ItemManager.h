#pragma once

// �� ��ϵ��� �����ϰ� ������ �����۵��� ��� ��� ���� ����
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
