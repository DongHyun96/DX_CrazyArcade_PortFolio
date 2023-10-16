#pragma once

namespace CollisionUtil
{

	Direction GetCollidedDirection(ColliderRect* myBody, ColliderRect* enteredBody);
	
	// myBody에 들어온 enteredBody 재위치
	void HandleCharacterCommonCollision(ColliderRect* myBody, ColliderRect* enteredBody);
	
}
