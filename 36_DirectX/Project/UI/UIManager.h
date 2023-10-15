#pragma once

class UIManager
{
public:

	virtual ~UIManager() = default;

public:
	
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void Init() = 0;


};
