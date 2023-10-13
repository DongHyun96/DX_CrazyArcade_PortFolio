#include "Framework.h"
#include "ItemManager.h"

vector<Item*> ItemManager::items{};

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
	for (Item* item : items)
		delete item;
}

void ItemManager::Update()
{
	for (Item* item : items)
		item->Update();

	Item::SetSpawnSoundPlayed(false);

	HandleCollisions();
}

void ItemManager::Render()
{
	for (Item* item : items)
		item->Render();
}

void ItemManager::AddItem(Item* item)
{
	if (!item) return;
	items.push_back(item);
}

void ItemManager::HandleCollisions()
{
	for (Item* item : items)
	{
		if (!item->GetIsActive()) continue;

		for (Character* player : GM->GetWholePlayers())
			item->GetBody()->AABBCollision(player->GetBody()->GlobalPosition(), player);

	}
}
