#include "Framework.h"
#include "Camera.h"


Camera::Camera()
{
	viewBuffer = new MatrixBuffer();

	transform = new Transform();
	
	transform->zDepth = 0.f;
}

Camera::~Camera()
{
	delete viewBuffer;
	delete transform;
}

void Camera::Update()
{
	transform->Update();

	if (!target)
		FreeMode();
	else
		TargetMode();

	if (KEY_PRESS(VK_SHIFT))
		speed = 300.f;
	else
		speed = 100.f;
}

void Camera::Set()
{
	Matrix viewMatrix = XMMatrixInverse(nullptr, transform->GetWorld());

	viewBuffer->SetData(viewMatrix);
	viewBuffer->VSSetBuffer(1);

}

void Camera::FreeMode()
{
	Vector2 moveDir{};

	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS('A'))
			moveDir.x += -1;

		if (KEY_PRESS('D'))
			moveDir.x += 1;

		if (KEY_PRESS('S'))
			moveDir.y -= 1;

		if (KEY_PRESS('W'))
			moveDir.y += 1;
	}

	if (moveDir.Length() != 0.f)
		moveDir.Normalize();

	transform->translation += moveDir * speed * Time::Delta();
}

void Camera::TargetMode()
{
	transform->translation = target->GlobalPosition() - offset;
}
