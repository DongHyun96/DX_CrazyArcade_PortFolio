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

void CollisionUtil::HandleCommonCollision(ColliderRect* myBody, ColliderRect* enteredBody)
{
	Direction collidedFace = GetCollidedDirection(myBody, enteredBody);

	if (collidedFace == DIR_LEFT)
		enteredBody->translation.x = myBody->Left() - enteredBody->LocalSize().x * 0.51f;

	else if (collidedFace == DIR_RIGHT)
		enteredBody->translation.x = myBody->Right() + enteredBody->LocalSize().x * 0.51f;

	else if (collidedFace == DIR_UP)
		enteredBody->translation.y = myBody->Top() + enteredBody->LocalSize().y * 0.51f;

	else if (collidedFace == DIR_DOWN)
		enteredBody->translation.y = myBody->Bottom() - enteredBody->LocalSize().y * 0.51f;
}
