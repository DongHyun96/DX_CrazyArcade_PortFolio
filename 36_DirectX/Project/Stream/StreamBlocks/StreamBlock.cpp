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
	body->SetColor(1, 0, 0);
}

StreamBlock::~StreamBlock()
{
	delete mainAnim;

	if (endAnim) delete endAnim;

	delete body;

	delete vertexShader;
	delete pixelShader;
	delete worldBuffer;
	delete colorBuffer;
}

void StreamBlock::Init()
{
	isActive = false;
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
	
	body->IsActive() = true;

	body->EnteredPointOwners().clear();
	body->EnteredBodies().clear();

	body->translation = Util::ConvertBoardIdxToWorldPos(spawnCoord);

	this->spawnCoord = spawnCoord;

	curAction = isEnd ? endAnim : mainAnim;

	curAction->Play();

	return this;
}

void StreamBlock::SetActive(const bool& isActive)
{
	this->isActive = isActive;
	
	if (!isActive) 
		Stream::EraseStreamDangerZone(spawnCoord); // Stream 클래스의 StreamDangerZone에서 자기자신의 위치 빼기
}

void StreamBlock::DisableBodyCollider()
{
	body->IsActive() = false;
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
			c->SetCharacterState(C_RETURN_IDLE);
			break;
		case C_CAPTURED: case C_RETURN_IDLE: case C_DEAD: case C_WIN: return;
		default:
			break;
		}

		return;
	}

	Item* item = dynamic_cast<Item*>(owner);

	if (item)
	{
		if (!item->GetIsActive()) return;
		if (item->GetItemState() != SPAWNED) return;

		item->SetActive(false);

		return;
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

		if (!block->IsHidable()) isActive = false;

		block->ApplyDamage();

		return;
	}
	
}
