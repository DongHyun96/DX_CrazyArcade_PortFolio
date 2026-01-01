#pragma once


/*
CONCRETE CLASS
Item field init helper class
아이템의 texObj와 item strategy를 여기서 initialize시킬 것임 (immediate든 Consumable이든 모두 이 과정을 거쳐야 하는 것은 동일)
*/
class ItemInitializer
{
public:

	ItemInitializer();
	~ItemInitializer();
	
	/// <summary>
	/// Item class의 texture object와 itemStrategy를 이 함수를 통해 초기화 / itemName에 따라 각기다른 초기화 진행
	/// </summary>
	/// <param name="itemName"> : 초기화 아이템 이름 </param>
	/// <param name="texObj"> : 아이템 이름에 따른 textureObj 초기화 (Double pointer형)</param>
	/// <param name="itemStrategy"> : 아이템 이름에 따른 itemStrategy 초기화 (Double pointer형)</param>
	static void CreateCommonFields(const ItemName& itemName, Object** texObj, ItemStrategy** itemStrategy);

private:

};
