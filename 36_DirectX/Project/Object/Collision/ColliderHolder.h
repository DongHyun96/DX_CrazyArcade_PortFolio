#pragma once

/// <summary> 
/// <para> Collider�� ��������� ������ �ִ� Ŭ�������� �ֻ��� Ŭ���� </para>
/// <para> Collision event call �޼��� ������ ����ȯ�� ���� Ư�� Ŭ���� Ÿ�� Ȯ�ο� </para>
/// </summary>
class ColliderHolder
{
public:
	ColliderHolder();
	virtual ~ColliderHolder() = default;
	
	virtual void Render() = 0;

};
