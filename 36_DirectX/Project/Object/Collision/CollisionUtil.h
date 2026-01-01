#pragma once

namespace CollisionUtil
{
	/// <summary>
	/// MyBody에 들어온 enteredBody가 myBody의 어느 방향으로 충돌하여 들어왔는지
	/// </summary>
	/// <param name="myBody"> : My body collider </param>
	/// <param name="enteredBody"> : myBody에 들어온 collider </param>
	/// <returns></returns>
	Direction GetCollidedDirection(ColliderRect* myBody, ColliderRect* enteredBody);
	
	/// <summary>
	/// <para> Block이나 Balloon과 Character에 대한 Collision handling								</para>
	/// <para> 기본 벽충돌처리와 더불어, 귀퉁이 부분에 위치하고 캐릭터가 이동하는 방향이 적절히 맞물릴 때, </para>
	/// <para> Lerp를 통한 캐릭터 위치조정을 처리함													</para>
	/// </summary>
	/// <param name="block"> : Block 또는 Balloon 또는 벽충돌처리를 할 물체의 ColliderRect body </param>
	/// <param name="character"> : Character body collider </param>
	/// <param name="characterSpeed"> : 캐릭터의 speed - Lerp를 통한 캐릭터 위치조정을 처리할 때 쓰임 </param>
	void HandleCharacterCommonCollision(ColliderRect* block, ColliderRect* character, const float& characterSpeed);
	
}
