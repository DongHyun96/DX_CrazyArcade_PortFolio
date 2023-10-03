#include "Framework.h"
#include "Character.h"


Character::Character(const CharacterType& cType)
{
	actionHandler = CharacterAnimFactory::CreateCharacterAnim(cType);

	vertexShader = new VertexShader(L"VertexTexture");
	pixelShader = new PixelShader(L"PixelTexture");

	worldBuffer = new MatrixBuffer();

	body = new ColliderRect(CELL_WORLD_SIZE);
	Util::SetTransformToGameBoard(body, { 6, 7 });
	
	// Character 자기자신의 Transform은 곧 Animation의 transform -> Animation transform의 부모를 bodyCollider로 둠
	this->SetParent(body);
}

Character::~Character()
{
	delete worldBuffer;
	delete vertexShader;
	delete pixelShader;

	delete actionHandler;

	delete body;
}

void Character::Update()
{
	Transform::Update();
	body->Update();
	
	body->UpdateZDepthToY();

	actionHandler->Update();

	actionHandler->UpdateAction(mainState, velocity);

	Move();
}

void Character::Render()
{
	worldBuffer->SetData(world);
	worldBuffer->VSSetBuffer(0);

	vertexShader->SetShader();
	pixelShader->SetShader();

	actionHandler->Render();

	body->Render();
}

void Character::SetAction(int state)
{

}
