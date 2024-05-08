#pragma once

// �� ��ϵ��� �����ϰ� ������ �����۵��� ��� ��� ���� ����
/*
CONCRETE CLASS
Block���� ������ ��, Block���� ������ Item�� ������ Ȯ���� ������ ����
Block���� ������ �������� ItemManager�� �Ѱܼ� ���� ����
*/
class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	void Update();
	void Render();

	void Init();

public:

	static vector<Item*>& GetItems() { return items; }
	
	static void AddItem(Item* item); // �� ��Ͽ��� �������� �����ߴٸ� ItemManager�� �־��

private:
	void HandleCollisions();

private:
	
	static vector<Item*> items;
};
