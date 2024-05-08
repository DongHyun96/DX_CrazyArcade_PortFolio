#pragma once


/*
CONCRETE CLASS
Item field init helper class
�������� texObj�� item strategy�� ���⼭ initialize��ų ���� (immediate�� Consumable�̵� ��� �� ������ ���ľ� �ϴ� ���� ����)
*/
class ItemInitializer
{
public:

	ItemInitializer();
	~ItemInitializer();
	
	/// <summary>
	/// Item class�� texture object�� itemStrategy�� �� �Լ��� ���� �ʱ�ȭ / itemName�� ���� ����ٸ� �ʱ�ȭ ����
	/// </summary>
	/// <param name="itemName"> : �ʱ�ȭ ������ �̸� </param>
	/// <param name="texObj"> : ������ �̸��� ���� textureObj �ʱ�ȭ (Double pointer��)</param>
	/// <param name="itemStrategy"> : ������ �̸��� ���� itemStrategy �ʱ�ȭ (Double pointer��)</param>
	static void CreateCommonFields(const ItemName& itemName, Object** texObj, ItemStrategy** itemStrategy);

private:

};
