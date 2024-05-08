#pragma once

/*
INTERFACE
Collider�� ��������� ������ �ִ� Ŭ�������� �ֻ��� Ŭ����
Collision event call �޼��� ������ ����ȯ�� ���� Ư�� Ŭ���� Ÿ�� Ȯ�ο�
*/
class ColliderHolder
{
public:
	ColliderHolder();
	virtual ~ColliderHolder() = default;
	
	virtual void Render() = 0;

};
