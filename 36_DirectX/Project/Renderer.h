#pragma once

class Renderer
{
public:
	virtual ~Renderer() = default;

	virtual void Render() = 0;

private:

};
