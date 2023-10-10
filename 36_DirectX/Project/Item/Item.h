#pragma once

/*
TODO - 아이템 사용 전략 패턴 만들기

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
	Object* texObj{}; // Body의 transform을 따라감



};
