#pragma once

namespace CollisionUtil
{
	/// <summary>
	/// MyBody�� ���� enteredBody�� myBody�� ��� �������� �浹�Ͽ� ���Դ���
	/// </summary>
	/// <param name="myBody"> : My body collider </param>
	/// <param name="enteredBody"> : myBody�� ���� collider </param>
	/// <returns></returns>
	Direction GetCollidedDirection(ColliderRect* myBody, ColliderRect* enteredBody);
	
	/// <summary>
	/// <para> Block�̳� Balloon�� Character�� ���� Collision handling								</para>
	/// <para> �⺻ ���浹ó���� ���Ҿ�, ������ �κп� ��ġ�ϰ� ĳ���Ͱ� �̵��ϴ� ������ ������ �¹��� ��, </para>
	/// <para> Lerp�� ���� ĳ���� ��ġ������ ó����													</para>
	/// </summary>
	/// <param name="block"> : Block �Ǵ� Balloon �Ǵ� ���浹ó���� �� ��ü�� ColliderRect body </param>
	/// <param name="character"> : Character body collider </param>
	/// <param name="characterSpeed"> : ĳ������ speed - Lerp�� ���� ĳ���� ��ġ������ ó���� �� ���� </param>
	void HandleCharacterCommonCollision(ColliderRect* block, ColliderRect* character, const float& characterSpeed);
	
}
