#pragma once


// 아이템의 texObj와 strategy를 여기서 initialize시킬 것임 (immediate든 Consumable이든 모두 이 과정을 거쳐야 하는 것은 동일)

class ItemInitializer
{

	friend class Item;
public:

	ItemInitializer();
	~ItemInitializer();
	
	static void CreateCommonFields(const ItemName& itemName, Object** texObj, ItemStrategy** itemStrategy);

private:

};
