#include "Framework.h"
#include "CollisionUtil.h"


Direction CollisionUtil::GetCollidedDirection(ColliderRect* myBody, ColliderRect* enteredBody)
{
	Vector2 dir = enteredBody->GlobalPosition() - myBody->GlobalPosition();

	Vector2 size = myBody->GlobalSize();

	Vector2 LU = Vector2(-size.x, +size.y);
	Vector2 RU = Vector2(+size.x, +size.y);
	Vector2 LD = Vector2(-size.x, -size.y);
	Vector2 RD = Vector2(+size.x, -size.y);

	if (Vector2::IsBetween(dir, LU, LD) && enteredBody->GlobalPosition().x < myBody->GlobalPosition().x)
		return DIR_LEFT;
	else if (Vector2::IsBetween(dir, RU, RD) && enteredBody->GlobalPosition().x > myBody->GlobalPosition().x)
		return DIR_RIGHT;
	else if (Vector2::IsBetween(dir, LU, RU) && enteredBody->GlobalPosition().y > myBody->GlobalPosition().y)
		return DIR_UP;
	else if (Vector2::IsBetween(dir, LD, RD) && enteredBody->GlobalPosition().y < myBody->GlobalPosition().y)
		return DIR_DOWN;

	return DIR_NONE;
}


void CollisionUtil::HandleCharacterCommonCollision(ColliderRect* block, ColliderRect* character, const float& characterSpeed)
{
	static const float SPEED_FACTOR = 0.15f;

	Direction collidedFace = GetCollidedDirection(block, character);

	if (collidedFace == DIR_LEFT || collidedFace == DIR_RIGHT)
	{
		character->translation.x = (collidedFace == DIR_LEFT) ? block->Left() - character->LocalSize().x * 0.5001f
																: block->Right() + character->LocalSize().x * 0.5001f;
		//D = 0.0016
		// 0.15f
		// characterSpeed * Time::Delta();
		// y값 조정
		if (character->Bottom() < block->Bottom())
		{
			if (character->Top() < block->Bottom() + block->LocalSize().y * 0.4f)
				character->translation.y = Util::Lerp(character->translation.y,
													  block->translation.y - CELL_WORLD_SIZE.y,
													  characterSpeed * Time::Delta() * SPEED_FACTOR);
		}
		else
		{
			if (character->Bottom() > block->Top() - block->LocalSize().y * 0.4f)
				character->translation.y = Util::Lerp(character->translation.y,
													  block->translation.y + CELL_WORLD_SIZE.y,
													  characterSpeed * Time::Delta() * SPEED_FACTOR);
		}
	}
	else if (collidedFace == DIR_UP || collidedFace == DIR_DOWN)
	{
		character->translation.y = (collidedFace == DIR_UP) ? block->Top() + character->LocalSize().y * 0.5001f
															  : block->Bottom() - character->LocalSize().y * 0.5001f;

		// x값 조정
		if (character->Left() < block->Left())
		{
			if (character->Right() < block->Left() + block->LocalSize().x * 0.4f)
				character->translation.x = Util::Lerp(character->translation.x,
												      block->translation.x - CELL_WORLD_SIZE.x,
												      characterSpeed * Time::Delta() * SPEED_FACTOR);
		}
		else
		{
			if (character->Left() > block->Right() - block->LocalSize().x * 0.4f)
				character->translation.x = Util::Lerp(character->translation.x,
													  block->translation.x + CELL_WORLD_SIZE.x,
													  characterSpeed * Time::Delta() * SPEED_FACTOR);
		}

	}
}
