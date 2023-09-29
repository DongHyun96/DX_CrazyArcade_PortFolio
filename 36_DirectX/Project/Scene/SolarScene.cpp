#include "Framework.h"
#include "SolarScene.h"

SolarScene::SolarScene()
{
	sun = new Planet(100.f, 5, {1.f, 0.f, 0.f, 1.f}, 1.f, 2.f);
	sun->translation = WIN_CENTER;

	earth = new Planet(50.f, 5, {0.f, 0.f, 1.f, 0.5f}, -5, -1);
	earth->translation = { 150.f, 150.f };

	earth->SetParent(sun);

	moon = new Planet(10, 4, { 1, 1, 0, 1 }, +3, +2);
	moon->translation = { 50, 50 };
	moon->SetParent(earth);
}

SolarScene::~SolarScene()
{
	delete sun;
	delete earth;
	delete moon;
}

void SolarScene::Update()
{
	sun->Update();

	earth->Update();
	moon->Update();
}

void SolarScene::Render()
{
	sun->Render();
	earth->Render();
	moon->Render();
}
