#pragma once

// �� ��ϵ��� �����ϰ� ������ �����۵��� ��� ��� ���� ����
class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	void Update();
	void Render();

	void Init();

	static vector<Item*>& GetItems() { return items; }
	
	static void AddItem(Item* item); // �� ��Ͽ��� �������� �����ߴٸ� ItemManager�� �־��

private:
	void HandleCollisions();

private:
	
	static vector<Item*> items;
};
