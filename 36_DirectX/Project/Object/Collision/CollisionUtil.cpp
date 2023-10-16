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

void CollisionUtil::HandleCharacterCommonCollision(ColliderRect* myBody, ColliderRect* enteredBody)
{
	Direction collidedFace = GetCollidedDirection(myBody, enteredBody);

	if (collidedFace == DIR_LEFT || collidedFace == DIR_RIGHT)
	{
		enteredBody->translation.x = (collidedFace == DIR_LEFT) ? myBody->Left() - enteredBody->LocalSize().x * 0.501f
																: myBody->Right() + enteredBody->LocalSize().x * 0.501f;

		// y값 조정
		if (enteredBody->Bottom() < myBody->Bottom())
		{
			if (enteredBody->Top() < myBody->Bottom() + myBody->LocalSize().y * 0.4f)
				enteredBody->translation.y = Util::Lerp(enteredBody->translation.y, myBody->translation.y - CELL_WORLD_SIZE.y, 0.15f);
		}
		else
		{
			if (enteredBody->Bottom() > myBody->Top() - myBody->LocalSize().y * 0.4f)
				enteredBody->translation.y = Util::Lerp(enteredBody->translation.y, myBody->translation.y + CELL_WORLD_SIZE.y, 0.15f);
		}
	}
	else if (collidedFace == DIR_UP || collidedFace == DIR_DOWN)
	{
		enteredBody->translation.y = (collidedFace == DIR_UP) ? myBody->Top() + enteredBody->LocalSize().y * 0.501f 
															  : myBody->Bottom() - enteredBody->LocalSize().y * 0.501f;

		// x값 조정
		if (enteredBody->Left() < myBody->Left())
		{
			if (enteredBody->Right() < myBody->Left() + myBody->LocalSize().x * 0.4f)
				enteredBody->translation.x = Util::Lerp(enteredBody->translation.x, myBody->translation.x - CELL_WORLD_SIZE.x, 0.15f);
		}
		else
		{
			if (enteredBody->Left() > myBody->Right() - myBody->LocalSize().x * 0.4f)
				enteredBody->translation.x = Util::Lerp(enteredBody->translation.x, myBody->translation.x + CELL_WORLD_SIZE.x, 0.15f);
		}

	}
}
