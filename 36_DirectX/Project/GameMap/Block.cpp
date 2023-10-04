#include "Framework.h"
#include "Block.h"

Block::Block(const BlockInfo& info)
	:Block(info.boardXY, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp)
{
}

Block::Block(Util::Coord boardXY, wstring texFile, Util::Coord frameXY, Util::Coord targetXY, Vector2 texWorldSize, BlockProperty bProp)
	:breakable(bProp.breakable), movable(bProp.movable), hidable(bProp.hidable)
{
	texWorldSize.y += Y_OFFSET; // offset 조정

	rectBody	= new ColliderRect(CELL_WORLD_SIZE);
	texObj		= new Object(texWorldSize, texFile, frameXY.x, frameXY.y, targetXY.x, targetXY.y);

	texObj->translation.y += (texWorldSize.y - CELL_WORLD_SIZE.y) * 0.5f; // local translation으로 tex의 위치 조정

	texObj->SetParent(rectBody); // 실제 body를 texture가 따라가게끔 처리할 것임

	Util::SetTransformToGameBoard(rectBody, boardXY);

	//Util::SetTransformToGameBoard(body, { 3, 4 });
	
	label = to_string(boardXY.x) + to_string(boardXY.y);

	// Setting Collider call back functions
	// 물줄기 위치 파악 -> 해당 위치에 있는 블록을 제거
	// player 움직임은 명확하게 떨어지지 않음(좌표가 딱딱 떨어지는 것이 아님) -> player movement 충돌은 실제 충돌처리로 처리
	if (hidable)
	{
		rectBody->SetPointEnterEvent(bind(&Block::OnColliderPointEnter, this, placeholders::_1));
		rectBody->SetPointExitEvent(bind(&Block::OnColliderPointExit, this, placeholders::_1));
	}
	else
	{
		rectBody->SetRectEnterEvent(bind(&Block::OnColliderRectEnter, this, placeholders::_1));
		rectBody->SetRectExitEvent(bind(&Block::OnColliderRectExit, this, placeholders::_1));
	}
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

	rectBody->UpdateZDepthToY();

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

bool Block::Move(const UINT& destBoardCoordX, const UINT& destBoardCoordY)
{
	return Move(Util::ConvertBoardIdxToWorldPos({ destBoardCoordX, destBoardCoordY }));
}

bool Block::Move(const Util::Coord& destCoord)
{
	return Move(Util::ConvertBoardIdxToWorldPos({ destCoord.x, destCoord.y }));
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

	if (leftDist < 1.f) // 도착
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

	// 1초를 0.25로 쪼개어 interaction을 줄 예정, texObj만 local translation x값을 조정하여 양옆으로 왔다갔다만 할 예정
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

void Block::OnColliderPointEnter(Transform* owner)
{
	if (hidable)
	{
		PlayBushInteraction();

		Character* c = dynamic_cast<Character*>(owner);
		
		if (c) c->SetVisible(false);

	}
	
}

void Block::OnColliderPointExit(Transform* owner)
{
	if (hidable)
	{
		PlayBushInteraction();

		Character* c = dynamic_cast<Character*>(owner);

		if (c) c->SetVisible(true);
	}
}

void Block::OnColliderRectEnter(Transform* owner)
{
	// Hidable 배제 (등록도 하지 않는다)
	if (movable)
	{
		// 얘 처리도 모호함.. --> 아예 클래스를 하나 파서 충돌체를 겉에 하나 더 주는 식으로 해서 처리하는 편도 나쁘지는 않을 듯함
	}
	else
	{
		Character* c = dynamic_cast<Character*>(owner);

		if (c) HandleCharacterCollision(c);
	}
}

void Block::OnColliderRectExit(Transform* owner)
{
	// Hidable 배제 (등록도 하지 않는다)

}

void Block::HandleCharacterCollision(Character* character)
{
	Vector2 dir = character->GetBody()->GlobalPosition() - this->GetBody()->GlobalPosition();

	Vector2 size = this->GetBody()->GlobalSize();

	Vector2 LU = Vector2(-size.x, +size.y);
	Vector2 RU = Vector2(+size.x, +size.y);
	Vector2 LD = Vector2(-size.x, -size.y);
	Vector2 RD = Vector2(+size.x, -size.y);

	// LEFT
	if (Vector2::IsBetween(dir, LU, LD) && character->GetBody()->GlobalPosition().x < this->GetBody()->GlobalPosition().x)
	{
		character->GetBody()->translation.x = this->GetBody()->Left() - character->GetBody()->LocalSize().x * 0.51f;
	}
	// RIGHT
	else if (Vector2::IsBetween(dir, RU, RD) && character->GetBody()->GlobalPosition().x > this->GetBody()->GlobalPosition().x)
	{
		character->GetBody()->translation.x = this->GetBody()->Right() + character->GetBody()->LocalSize().x * 0.51f;
	}
	// UP
	else if (Vector2::IsBetween(dir, LU, RU) && character->GetBody()->GlobalPosition().y > this->GetBody()->GlobalPosition().y)
	{
		character->GetBody()->translation.y = this->GetBody()->Top() + character->GetBody()->LocalSize().y * 0.51f;
	}
	// DOWN
	else if (Vector2::IsBetween(dir, LD, RD) && character->GetBody()->GlobalPosition().y < this->GetBody()->GlobalPosition().y)
	{
		character->GetBody()->translation.y = this->GetBody()->Bottom() - character->GetBody()->LocalSize().y * 0.51f;
	}

}

void Block::Debug()
{
	assert(label != "");

	if (ImGui::BeginMenu(label.c_str()))
	{
		ImGui::InputFloat2("Translation", (float*)&rectBody->translation);

		Vector2 gp = rectBody->GlobalPosition();
		ImGui::InputFloat2("worldPos", (float*)&gp);

		ImGui::InputFloat2("Destination", (float*)&destination);

		ImGui::DragFloat("zDepth", &(rectBody->zDepth));
		

		ImGui::EndMenu();
	}


}

void Block::Debug(const string& label)
{
	rectBody->Debug(label);
}
