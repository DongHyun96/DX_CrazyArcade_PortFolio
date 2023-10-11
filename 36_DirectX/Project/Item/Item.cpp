#include "Framework.h"
#include "Item.h"

bool Item::spawnSoundPlayed{};

Item::Item(const ItemName& itemName)
{
	body = new ColliderRect(CELL_WORLD_SIZE);

	body->SetPointEnterEvent(bind(&Item::OnColliderPointEnter, this, placeholders::_1));
	body->SetRectEnterEvent(bind(&Item::OnColliderRectEnter, this, placeholders::_1, placeholders::_2));

	// TODO : 각각의 texObj 생성 및 itemStrategy 초기화 하기
	ItemInitializer::CreateCommonFields(itemName, &texObj, &itemStrategy);

	texObj->SetParent(body);

	Util::SetTransformToGameBoard(body, {0, 0});
}

Item::~Item()
{
	delete body;
	delete texObj;
}

void Item::Update()
{
	if (!isActive)
		return;

	switch (itemState)
	{
	case HIDE:
		break;
	case SPAWNED:
	{
		static float spawnScaleSpeed = 5.f;
		
		if (body->scale.Length() > 0.999f)
		{
			body->scale = { 1, 1 };

			Util::PlayFloatingEffect(texObj->translation.y, spawned_timeChecker, spawned_ySpeed, SPAWNED_Y_UPDATE_TICK);
			
			break;
		}

		body->scale.x += spawnScaleSpeed * Time::Delta();
		body->scale.y += spawnScaleSpeed * Time::Delta();
	}
		break;
	case EARNED:
		break;
	case RESPAWN:
		break;
	default:
		break;
	}
	body->UpdateZDepthToY();
	body->Update();
	texObj->Update();

}

void Item::Render()
{
	if (!isActive)
		return;

	switch (itemState)
	{
	case HIDE:
		break;
	case SPAWNED:
		break;
	case EARNED:
		EarnedRenderHook(); // Hook Method  (자식에서 결정)
		break;
	case RESPAWN:
		break;
	default:
		break;
	}

	body->Render();
	texObj->Render();
}

bool Item::UseItem(Character* itemUser)
{
	return itemStrategy->UseStrategy(itemUser);
}

void Item::Spawn(const Vector2& spawnPos)
{
	if (!spawnSoundPlayed)
	{
		SOUND->Play("ItemSpawned", 1.f);
		spawnSoundPlayed = true;
	}

	body->translation = spawnPos;
	SetItemState(SPAWNED);
}

void Item::Respawn(const Vector2& src, const Vector2& dst)
{
}

void Item::SetItemState(const ItemState& itemState)
{
	// prevItemState
	if (this->itemState == SPAWNED)
	{
		body->scale = { 1, 1 };
		texObj->translation = { 0, 0 };
		spawned_timeChecker = 0.f;
		spawned_ySpeed = 50.f;
	}

	switch (itemState)
	{
	case SPAWNED:
		isActive = true;
		body->scale = {};
		break;
	case EARNED:
		EarnedSetterHook(); // Hook Method (자식에서 결정)
		break;
	case RESPAWN:
		break;
	default:
		break;
	}

	this->itemState = itemState;
}

void Item::OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner)
{
	// 물줄기 충돌 검사 (를 여기서 하려 했지만 StreamBlock에서 하기로 함)
	/*StreamBlock* streamblock = dynamic_cast<StreamBlock*>(owner);

	if (streamblock)
	{
		isActive = false;
		return;
	}*/

}

