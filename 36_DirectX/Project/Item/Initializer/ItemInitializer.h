#pragma once


// �������� texObj�� strategy�� ���⼭ initialize��ų ���� (immediate�� Consumable�̵� ��� �� ������ ���ľ� �ϴ� ���� ����)

class ItemInitializer
{
public:

	ItemInitializer();
	~ItemInitializer();
	
	static void CreateCommonFields(const ItemName& itemName, Object** texObj, ItemStrategy** itemStrategy);

private:

};
