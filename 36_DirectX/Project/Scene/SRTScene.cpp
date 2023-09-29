#include "Framework.h"
#include "SRTScene.h"


SRTScene::SRTScene()
{
	world = XMMatrixIdentity();

	object = new Object(Vector2(100, 100));

	worldBuffer = new MatrixBuffer();
}

SRTScene::~SRTScene()
{
	delete object;
	delete worldBuffer;
}

void SRTScene::Update()
{
	S		= XMMatrixScaling(scale.x, scale.y, 1.f);
	R		= XMMatrixRotationZ(angle);
	T		= XMMatrixTranslation(translation.x, translation.y, 0.f);

	translation = { 100.f, 100.f };

	world	= S * R * T;

	world2 = XMMatrixTranslation(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f, 0.f);

	// �� ���� ���ϴ� matrix�� world�� ���ο� �θ� ��
	world2 *= world;
}

void SRTScene::Render()
{

	// ���ο� data�� ����
	worldBuffer->SetData(world);
	worldBuffer->VSSetBuffer(0);

	object->Render(); // Draw call

	// ���ο� data�� ����
	worldBuffer->SetData(world2);
	worldBuffer->VSSetBuffer(0);

	object->Render(); // ���ο� draw call

	ImGui::SliderFloat2("Translation", (float*)&translation, -WIN_WIDTH, +WIN_WIDTH);
	ImGui::DragFloat2("Scale", (float*)&scale, 0.01f);

}
