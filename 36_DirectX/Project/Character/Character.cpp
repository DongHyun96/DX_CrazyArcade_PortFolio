#include "Framework.h"
#include "Character.h"


Character::Character(const CharacterType& cType)
{
	Vector2 characterBodySize = { CELL_WORLD_SIZE.x - 30.f, CELL_WORLD_SIZE.y - 30.f };
	Vector2 pushColSize = { CELL_WORLD_SIZE.x - 15.f, CELL_WORLD_SIZE.y - 15.f };

	//Vector2 characterBodySize = { CELL_WORLD_SIZE.x - 10.f, CELL_WORLD_SIZE.y - 10.f };
	//Vector2 pushColSize = { CELL_WORLD_SIZE.x + 10.f, CELL_WORLD_SIZE.y + 10.f };

	body = new ColliderRect(characterBodySize);
	body->SetColliderTag(CHARACTER);

	pushCollider = new ColliderRect(pushColSize);
	pushCollider->SetColliderTag(CHARACTER_PUSH);
	pushCollider->SetColor(1, 0, 0);

	Util::SetTransformToGameBoard(body, { 7, MAP_ROW - 7 });
	pushCollider->SetParent(body);

	actionHandler = CharacterAnimFactory::CreateCharacterAnim(cType, body);

	colorBuffer = new ColorBuffer();

}

Character::~Character()
{
	delete actionHandler;

	delete body;
	delete pushCollider;

	delete colorBuffer;

}

void Character::Update()
{
	body->Update();
	pushCollider->Update();

	body->UpdateZDepthToY();

	Move();
	DeployBalloon();

	actionHandler->Update();
	actionHandler->UpdateAction(mainState, velocity);

	HandleBoundary();
}

void Character::Render()
{
	//colorBuffer->SetData(Vector4(1, 0, 1, 1.f));
	if (!visible)
		return;

	colorBuffer->PSSetBuffer(0);

	actionHandler->Render();

	body->Render();
	pushCollider->Render();
}

void Character::Debug()
{
	assert(label != "");

	body->Debug(label);
}

void Character::HandleBoundary()
{
	if (body->Left() < GM->GetMapL())
		body->translation.x = GM->GetMapL() + body->LocalSize().x * 0.51f;
	if (body->Right() > GM->GetMapR())
		body->translation.x = GM->GetMapR() - body->LocalSize().x * 0.51f;
	if (body->Top() > GM->GetMapT())
		body->translation.y = GM->GetMapT() - body->LocalSize().y * 0.51f;
	if (body->Bottom() < GM->GetMapB())
		body->translation.y = GM->GetMapB() + body->LocalSize().y * 0.51f;
	//else if (body->Bottom() < 0)
}
