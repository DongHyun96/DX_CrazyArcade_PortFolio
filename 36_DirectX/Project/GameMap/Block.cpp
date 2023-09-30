#include "Framework.h"
#include "Block.h"

Block::Block(pair<UINT, UINT> boardXY, wstring texFile, pair<UINT, UINT> frameXY, pair<UINT, UINT> targetXY, Vector2 texWorldSize, BlockProperty bProp)
	:breakable(bProp.breakable), movable(bProp.movable), hidable(bProp.hidable)
{
	texWorldSize.y += Y_OFFSET; // offset ����

	rectBody	= new ColliderRect(Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW));
	texObj		= new Object(texWorldSize, texFile, frameXY.first, frameXY.second, targetXY.first, targetXY.second);

	texObj->translation.y += Y_OFFSET / 2; // offset ����

	texObj->SetParent(rectBody); // ���� body�� texture�� ���󰡰Բ� ó���� ����

	Util::SetTransformToGameBoard(rectBody, boardXY);

	rectBody->zDepth = rectBody->GlobalPosition().y;
}

Block::~Block()
{
	delete rectBody;
	delete texObj;
}

void Block::Update()
{
	if (!isActive)
		return;

	rectBody->Update();
	texObj->Update();
}

void Block::Render()
{
	if (!isActive)
		return;

	rectBody->Render();
	texObj->Render();
}

void Block::PlayBushInteraction()
{
}

void Block::Move(Vector2 destination)
{
}

void Block::ApplyDamage()
{
}
