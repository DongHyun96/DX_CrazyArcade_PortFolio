#pragma once

namespace CollisionUtil
{

	Direction GetCollidedDirection(ColliderRect* myBody, ColliderRect* enteredBody);
	
	// myBody�� ���� enteredBody ����ġ
	void HandleCommonCollision(ColliderRect* myBody, ColliderRect* enteredBody);
	
}
