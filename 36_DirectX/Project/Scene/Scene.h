#pragma once

/* INTERFACE */
class Scene
{
public:
	virtual ~Scene() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;

};