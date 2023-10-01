#include "Framework.h"
#include "Block.h"

Block::Block(Util::Coord boardXY, wstring texFile, Util::Coord frameXY, Util::Coord targetXY, Vector2 texWorldSize, BlockProperty bProp)
	:breakable(bProp.breakable), movable(bProp.movable), hidable(bProp.hidable)
{
	boardPos = { boardXY.x, boardXY.y };
	
	texWorldSize.y += Y_OFFSET; // offset ����

	rectBody	= new ColliderRect(CELL_WORLD_SIZE);
	texObj		= new Object(texWorldSize, texFile, frameXY.x, frameXY.y, targetXY.x, targetXY.y);

	texObj->translation.y += (texWorldSize.y - CELL_WORLD_SIZE.y) * 0.5f; // local translation���� tex�� ��ġ ����

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

	Move();
	HandleBushInteract();

	rectBody->Update();
	texObj->Update();

}

void Block::Render()
{
	if (!isActive)
		return;

	rectBody->Render();
	texObj->Render();

	//Debug();
}

void Block::PlayBushInteraction()
{
	if (currentlyBushing)
		return;

	currentlyBushing = true;
}

void Block::Move(const UINT& destBoardCoordX, const UINT& destBoardCoordY)
{
	if (Move(Util::ConvertBoardIdxToWorldPos({ destBoardCoordX, destBoardCoordY })))
		boardPos = { destBoardCoordX, destBoardCoordY };
}

void Block::Move(const Util::Coord& destCoord)
{
	if (Move(Util::ConvertBoardIdxToWorldPos({ destCoord.x, destCoord.y })))
		boardPos = destCoord;
}

bool Block::Move(Vector2 destination)
{
	if (!movable)
		return false;

	if (currentlyMoving)
		return false;

	currentlyMoving = true;
	this->destination = destination;

	return true;
}

void Block::ApplyDamage()
{
	if (!isActive)
		return;

	hp--;

	if (hp <= 0)
		isActive = false;
}

void Block::Move()
{
	if (!currentlyMoving || !movable)
		return;

	static const float speed = 400.f;
	
	Vector2 direction = destination - rectBody->translation;

	float leftDist = direction.Length();

	if (leftDist < 1.f) // ����
	{
		rectBody->translation = destination;
		currentlyMoving = false;
		return;
	}

	rectBody->translation += direction.GetNormal() * speed * Time::Delta();
}

void Block::HandleBushInteract()
{
	if (!hidable || !currentlyBushing)
		return;

	interactTime += Time::Delta();

	// 1�ʸ� 0.25�� �ɰ��� interaction�� �� ����, texObj�� local translation x���� �����Ͽ� �翷���� �Դٰ��ٸ� �� ����
	if		(interactTime < 0.15f) texObj->translation.x = -10.f;
	else if (interactTime < 0.3f)	texObj->translation.x = 10.f;
	else if (interactTime < 0.45f) texObj->translation.x = -10.f;
	else if (interactTime < 0.6f)	texObj->translation.x = 10.f;
	else
	{
		interactTime -= 0.6f;
		texObj->translation.x = 0.f;
		currentlyBushing = false;
	}

}

void Block::Debug()
{
	assert(label != "");

	if (ImGui::BeginMenu(label.c_str()))
	{
		ImGui::InputInt2("BoardPos", (int*)&boardPos);

		ImGui::InputFloat2("Translation", (float*)&rectBody->translation);

		Vector2 gp = rectBody->GlobalPosition();
		ImGui::InputFloat2("worldPos", (float*)&gp);

		ImGui::InputFloat2("Destination", (float*)&destination);

		

		ImGui::EndMenu();
	}


}
