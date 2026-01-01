#include "Framework.h"
#include "Planet.h"


Planet::Planet(float radius, UINT sectorCount, Vector4 color, float rotSpeed, float revSpeed)
	:Polygons(radius, sectorCount, color), rotSpeed(rotSpeed), revSpeed(revSpeed)
{
}

Planet::~Planet()
{
}

void Planet::UpdateWorld()
{
	S = XMMatrixScaling(scale.x, scale.y, 1.f);
	R = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	T = XMMatrixTranslation(translation.x, translation.y, 0.f);

	world = S * R * T;

	if (parent) // 부모의 위치정보만 받을 것임
	{
		Matrix revMatrix = XMMatrixRotationZ(revAngle);

		XMFLOAT4X4 pWorld;

		XMStoreFloat4x4(&pWorld, parent->GetWorld());

		Matrix pGlobalPos = XMMatrixTranslation(pWorld._41, pWorld._42, 0.f);

		this->world *= revMatrix * pGlobalPos;
	}
}

void Planet::Update()
{
	UpdateWorld();

	rotation.z += rotSpeed * Time::Delta();

	revAngle += revSpeed * Time::Delta();
}
