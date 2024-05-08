#include "Framework.h"
#include "Dart.h"


Dart::Dart()
{
	body = new ColliderRect(CELL_WORLD_SIZE);
	body->scale = { 0.4f, 0.3f };

	for (UINT i = 0; i < 4; i++)
	{
		// UP, DOWN, LEFT, RIGHT
		dirTexMap[(Direction)i] = new Object(CELL_WORLD_SIZE, L"InGame/Item/Dart" + to_wstring(i) + L".png");
		dirTexMap[(Direction)i]->SetParent(body);
	}

	curTexObj = dirTexMap[DIR_UP];

	Util::SetTransformToGameBoard(body, { 0, 0 });
	
	body->zDepth = 0.f;

	body->SetRectEnterEvent(bind(&Dart::OnColliderRectEnter, this, placeholders::_1, placeholders::_2));
}

Dart::~Dart()
{
	for (auto& p : dirTexMap)
		delete p.second;

	dirTexMap.clear();

	delete body;
}

void Dart::Init()
{
	isActive = false;

	direction = {};
}

void Dart::Update()
{
	if (!isActive) return;

	body->Update();
	curTexObj->Update();

	body->translation += direction * SPEED * Time::Delta();

	HandleBoundary();
}

void Dart::Render()
{
	//Debug();
	if (!isActive) return;

	body->Render();
	curTexObj->Render();

}

void Dart::Debug()
{
	ImGui::BeginGroup();

	ImGui::Begin("bodyPos");
	ImGui::InputFloat2("XY", (float*)&body->translation);
	ImGui::End();

	ImGui::EndGroup();
}

void Dart::Spawn(const Vector2& spawnPos, const Direction& fireDirection)
{
	isActive = true;
	
	body->translation = spawnPos;
	
	switch (fireDirection)
	{
	case DIR_LEFT:
		direction = { -1, 0 };
		break;
	case DIR_RIGHT:
		direction = { 1, 0 };
		break;
	case DIR_UP:
		direction = { 0, 1 };
		break;
	case DIR_DOWN:
		direction = { 0, -1 };
		break;
	default:
		break;
	}
	curTexObj = dirTexMap[fireDirection];
}

void Dart::HandleBoundary()
{
	if (body->Right() < GM->GetMapL() || body->Left() > GM->GetMapR() ||
		body->Bottom() > GM->GetMapT() || body->Top() < GM->GetMapB())
	{
		isActive = false;
	}
}

void Dart::OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner)
{
	// Block과의 충돌은 blockManager에서 담당

	Balloon* balloon = dynamic_cast<Balloon*>(owner);

	if (balloon)
	{
		balloon->Explode();
		isActive = false;
	}
}
