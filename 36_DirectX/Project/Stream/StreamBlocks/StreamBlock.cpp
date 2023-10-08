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

	curAction = isEnd ? endAnim : mainAnim;

	curAction->Play();

	return this;
}
