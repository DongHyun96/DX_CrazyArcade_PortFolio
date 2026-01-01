#pragma once
class Planet : public Polygons
{
public:
	Planet(float radius, UINT sectorCount, Vector4 color, float rotSpeed, float revSpeed);
	~Planet();

	void UpdateWorld();

	void Update();

private:
	float rotSpeed{};
	
	float revSpeed{};
	float revAngle{};
};
