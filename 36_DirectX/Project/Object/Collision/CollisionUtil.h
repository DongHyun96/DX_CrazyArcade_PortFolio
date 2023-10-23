#pragma once

namespace CollisionUtil
{

	Direction GetCollidedDirection(ColliderRect* myBody, ColliderRect* enteredBody);
	
	// myBody�� ���� enteredBody ����ġ
	void HandleCharacterCommonCollision(ColliderRect* block, ColliderRect* character, const float& characterSpeed);
	
}
