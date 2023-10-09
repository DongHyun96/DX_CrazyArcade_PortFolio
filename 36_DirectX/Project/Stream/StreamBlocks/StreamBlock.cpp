#include "Framework.h"
#include "StreamBlock.h"

StreamBlock::StreamBlock()
{
	body = new ColliderRect(CELL_WORLD_SIZE);
	body->zDepth = FAR_Z - 20.f;

	Util::SetTransformToGameBoard(body, {0, 0});

	vertexShader	= new VertexShader(L"VertexTexture");
	pixelShader		= new PixelShader(L"PixelTexture");
	worldBuffer		= new MatrixBuffer();
	colorBuffer		= new ColorBuffer();

	body->SetPointEnterEvent(bind(&StreamBlock::OnColliderPointEnter, this, placeholders::_1));
	body->SetRectEnterEvent(bind(&StreamBlock::OnColliderRectEnter, this, placeholders::_1, placeholders::_2));
}

StreamBlock::~StreamBlock()
{
	delete mainAnim;

	if (endAnim) delete endAnim;

	delete vertexShader;
	delete pixelShader;
	delete worldBuffer;
	delete colorBuffer;
}

void StreamBlock::Update()
{
	if (!isActive)
		return;

	body->Update();

	curAction->Update();
}

void StreamBlock::Render()
{
	if (!isActive)
		return;

	worldBuffer->SetData(body->GetWorld());
	worldBuffer->VSSetBuffer(0);

	vertexShader->SetShader();
	pixelShader->SetShader();

	colorBuffer->PSSetBuffer(0);

	curAction->Render();
	body->Render();

}

StreamBlock* StreamBlock::Spawn(const Util::Coord& spawnCoord, const bool& isEnd)
{
	this->isEnd = isEnd;
	isActive = true;

	body->translation = Util::ConvertBoardIdxToWorldPos(spawnCoord);

	this->spawnCoord = spawnCoord;

	curAction = isEnd ? endAnim : mainAnim;

	curAction->Play();

	return this;
}

void StreamBlock::OnColliderPointEnter(ColliderHolder* owner)
{
	Character* c = dynamic_cast<Character*>(owner);

	if (c)
	{
		CharacterState cs = c->GetCharacterState();
		switch (cs)
		{
		case C_IDLE:
			c->SetCharacterState(C_CAPTURED);
			break;
		case C_SPACECRAFT: case C_OWL: case C_TURTLE:
			break;
		case C_CAPTURED: case C_RETURN_IDLE: case C_DEAD: return;
		default:
			break;
		}
	}
}

void StreamBlock::OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner)
{
	Balloon* balloon = dynamic_cast<Balloon*>(owner);

	if (balloon)
	{
		if (!balloon->Active()) return;

		balloon->Explode();
		return;
	}

	Block* block = dynamic_cast<Block*>(owner);

	if (block)
	{
		if (!block->IsActive()) return;

		block->ApplyDamage();
		
		if (!block->IsHidable()) isActive = false;

		return;
	}
}
