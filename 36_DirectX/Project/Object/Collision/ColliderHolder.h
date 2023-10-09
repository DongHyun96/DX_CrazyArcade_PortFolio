#pragma once
class ColliderHolder
{
public:
	ColliderHolder();
	virtual ~ColliderHolder() = default;
	
	virtual void Render() = 0;

};
