#include "Framework.h"
#include "Transform.h"


Transform::Transform()
{
		S = XMMatrixIdentity();
		R = XMMatrixIdentity();
		T = XMMatrixIdentity();
	world = XMMatrixIdentity();

}

Transform::~Transform()
{
}

void Transform::Update()
{
	UpdateWorld();
}

void Transform::UpdateWorld()
{
	Matrix P = XMMatrixTranslation(pivot.x, pivot.y, 0.f);
	Matrix IP = XMMatrixInverse(nullptr, P);

	S = XMMatrixScaling(scale.x, scale.y, 1.f);
	R = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	T = XMMatrixTranslation(translation.x, translation.y, zDepth);
	//T = XMMatrixTranslation(translation.x, translation.y, 0.f);


	world = IP * S * R * T * P;

	if (parent)
		this->world *= parent->world;

	// Globals

	XMVECTOR outS, outR, outT;

	XMMatrixDecompose(&outS, &outR, &outT, world); // Decompose S, R, T로 분해해주는 함수

	XMStoreFloat2(&globalScale, outS);
	XMStoreFloat2(&globalPosition, outT);

	// Update Right vector, up vector
	XMFLOAT4X4 floatWorld;

	XMStoreFloat4x4(&floatWorld, world);

	right = Vector2(floatWorld._11, floatWorld._12).GetNormal();
	   up = Vector2(floatWorld._21, floatWorld._22).GetNormal();

}

void Transform::UpdateZDepthToY()
{
	zDepth = globalPosition.y;
}

void Transform::Debug()
{
	assert(label != "");

	if (ImGui::BeginMenu(label.c_str()))
	{
		ImGui::DragFloat2	("Scale", (float*)&scale, 0.1f, 0.1f, 50.f);
		ImGui::SliderAngle	("Rotation", &rotation.z);
		ImGui::DragFloat2	("Translation", (float*)&translation, 1.f, -WIN_WIDTH, WIN_WIDTH);
		ImGui::DragFloat	("ZDepth", &zDepth);

		ImGui::InputFloat2	("GlobalScale", (float*)&globalScale);
		ImGui::InputFloat2  ("GlobalPos", (float*)&globalPosition);

		ImGui::EndMenu();

	}
}

void Transform::Debug(const string& label)
{
	if (ImGui::BeginMenu(label.c_str()))
	{
		ImGui::DragFloat2("Scale", (float*)&scale, 0.1f, 0.1f, 50.f);
		ImGui::SliderAngle("Rotation", &rotation.z);
		ImGui::DragFloat2("Translation", (float*)&translation, 1.f, -WIN_WIDTH, WIN_WIDTH);
		ImGui::DragFloat("ZDepth", &zDepth);

		ImGui::InputFloat2("GlobalScale", (float*)&globalScale);
		ImGui::InputFloat2("GlobalPos", (float*)&globalPosition);

		ImGui::EndMenu();

	}
}
