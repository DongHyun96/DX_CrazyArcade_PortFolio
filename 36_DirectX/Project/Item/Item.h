#pragma once

/*
TODO - ������ ��� ���� ���� �����

*/


class Item
{
public:
	Item();
	~Item();

	void Update();
	void Render();

	
private:

	ColliderRect* body{};
	Object* texObj{}; // Body�� transform�� ����



};
