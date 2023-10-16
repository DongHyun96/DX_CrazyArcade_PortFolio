#pragma once

namespace CollisionUtil
{

	Direction GetCollidedDirection(ColliderRect* myBody, ColliderRect* enteredBody);
	
	// myBody�� ���� enteredBody ����ġ
	void HandleCharacterCommonCollision(ColliderRect* myBody, ColliderRect* enteredBody);
	
}
