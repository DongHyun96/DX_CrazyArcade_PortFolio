#pragma once

/*
INTERFACE
Collider를 멤버변수로 가지고 있는 클래스들의 최상위 클래스
Collision event call 메서드 내에서 형변환을 통한 특정 클래스 타입 확인용
*/
class ColliderHolder
{
public:
	ColliderHolder();
	virtual ~ColliderHolder() = default;
	
	virtual void Render() = 0;

};
