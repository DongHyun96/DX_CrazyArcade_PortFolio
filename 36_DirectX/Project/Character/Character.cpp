#include "Framework.h"
#include "Character.h"


Character::Character(const CharacterType& cType)
{
	Vector2 characterBodySize = { CELL_WORLD_SIZE.x - 10.f, CELL_WORLD_SIZE.y - 10.f };

	body = new ColliderRect(CELL_WORLD_SIZE);

	Util::SetTransformToGameBoard(body, { 3, 4 });

	actionHandler = CharacterAnimFactory::CreateCharacterAnim(cType, body);

	colorBuffer = new ColorBuffer();
}

Character::~Character()
{
	delete actionHandler;

	delete body;

	delete colorBuffer;
}

void Character::Update()
{
	body->Update();
	
	body->UpdateZDepthToY();

	Move();

	actionHandler->Update();
	actionHandler->UpdateAction(mainState, velocity);

}

void Character::Render()
{
	//colorBuffer->SetData(Vector4(1, 0, 1, 1.f));
	if (!visible)
		return;

	colorBuffer->PSSetBuffer(0);

	actionHandler->Render();

	body->Render();
}

void Character::Debug()
{
	assert(label != "");

	body->Debug(label);
}
