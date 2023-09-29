#include "Framework.h"
#include "TutorialScene.h"


TutorialScene::TutorialScene()
{
	object = new Object(Vector2(100, 100));

	worldMatrix = XMMatrixIdentity();
	worldBuffer = new MatrixBuffer();

	S._11 = 1;
	S._22 = 1;
	S._33 = 1;
	S._44 = 1;

	R._11 = 1;
	R._22 = 1;
	R._33 = 1;
	R._44 = 1;

	T._11 = 1;
	T._22 = 1;
	T._33 = 1;
	T._44 = 1;

}

TutorialScene::~TutorialScene()
{
	delete object;

	delete worldBuffer;

}

void TutorialScene::Update()
{
	// Scale
	if (KEY_PRESS(VK_LEFT))
		S._11 -= Time::Delta();
	if (KEY_PRESS(VK_RIGHT))
		S._11 += Time::Delta();
	if (KEY_PRESS(VK_DOWN))
		S._22 -= Time::Delta();
	if (KEY_PRESS(VK_UP))
		S._22 += Time::Delta();

	// Rotation
	if (KEY_PRESS('Q'))
		theta += Time::Delta();

	if (KEY_PRESS('E'))
		theta -= Time::Delta();

	R._11 = cos(theta);
	R._12 = sin(theta);
	R._21 = -sin(theta);
	R._22 = cos(theta);


	// Translation
	if (KEY_PRESS('A'))
		T._41 -= 300 * Time::Delta();

	if (KEY_PRESS('D'))
		T._41 += 300 * Time::Delta();

	if (KEY_PRESS('S'))
		T._42 -= 300 * Time::Delta();

	if (KEY_PRESS('W'))
		T._42 += 300 * Time::Delta();

	XMMATRIX mS = XMLoadFloat4x4(&S);
	XMMATRIX mR = XMLoadFloat4x4(&R);
	XMMATRIX mT = XMLoadFloat4x4(&T);

	worldMatrix = mS * mR * mT;
}

void TutorialScene::Render()
{
	worldBuffer->SetData(worldMatrix);
	worldBuffer->VSSetBuffer(0);

	object->Render();
}
