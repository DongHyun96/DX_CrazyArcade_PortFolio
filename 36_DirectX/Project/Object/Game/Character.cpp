#include "Framework.h"
#include "Character.h"


Character::Character()
{
	vertexShader = new VertexShader(L"VertexTexture");
	pixelShader = new PixelShader(L"PixelTexture");

	worldBuffer = new MatrixBuffer();
}

Character::~Character()
{
	for (pair<int, Animation*> action : actions)
		delete action.second;

	actions.clear();

	delete worldBuffer;

	delete vertexShader;
	delete pixelShader;
}

void Character::Update()
{
	if (!curAction)
		return;

	curAction->Update();
	Transform::Update();
}

void Character::Render()
{
	if (!curAction)
		return;

	worldBuffer->SetData(world);
	worldBuffer->VSSetBuffer(0);

	vertexShader->SetShader();
	pixelShader->SetShader();


	curAction->Render();
}

void Character::SetAction(int state)
{
	if (this->state == state)
		return;

	this->state = state;

	curAction = actions[state];
	curAction->Play();
}

