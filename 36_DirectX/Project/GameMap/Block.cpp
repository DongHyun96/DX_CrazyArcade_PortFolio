#include "Framework.h"
#include "Block.h"

Block::Block(const BlockInfo& info)
	:Block(info.boardXY, info.file, info.frameXY, info.targetXY, info.texWorldSize, info.bProp)
{
}

Block::Block(Util::Coord boardXY, wstring texFile, Util::Coord frameXY, Util::Coord targetXY, Vector2 texWorldSize, BlockProperty bProp)
	:breakable(bProp.breakable), movable(bProp.movable), hidable(bProp.hidable)
{
	texWorldSize.y += Y_OFFSET; // offset ����

	rectBody	= new ColliderRect(CELL_WORLD_SIZE);
	texObj		= new Object(texWorldSize, texFile, frameXY.x, frameXY.y, targetXY.x, targetXY.y);

	texObj->translation.y += (texWorldSize.y - CELL_WORLD_SIZE.y) * 0.5f; // local translation���� tex�� ��ġ ����

	texObj->SetParent(rectBody); // ���� body�� texture�� ���󰡰Բ� ó���� ����

	Util::SetTransformToGameBoard(rectBody, boardXY);

	//Util::SetTransformToGameBoard(body, { 3, 4 });
	
	label = to_string(boardXY.x) + to_string(boardXY.y);

	// Setting Collider call back functions
	// ���ٱ� ��ġ �ľ� -> �ش� ��ġ�� �ִ� ����� ����
	// player �������� ��Ȯ�ϰ� �������� ����(��ǥ�� ���� �������� ���� �ƴ�) -> player movement �浹�� ���� �浹ó���� ó��
	if (hidable)
	{
		rectBody->SetPointEnterEvent(bind(&Block::OnColliderPointEnter, this, placeholders::_1));
		rectBody->SetPointStayEvent(bind(&Block::OnColliderPointStay, this, placeholders::_1));
		rectBody->SetPointExitEvent(bind(&Block::OnColliderPointExit, this, placeholders::_1));
	}
	else
	{
		rectBody->SetRectEnterEvent(bind(&Block::OnColliderRectEnter, this, placeholders::_1, placeholders::_2));
		rectBody->SetRectStayEvent(bind(&Block::OnColliderRectStay, this, placeholders::_1, placeholders::_2));
		rectBody->SetRectExitEvent(bind(&Block::OnColliderRectExit, this, placeholders::_1, placeholders::_2));
	}

	destroyedAnim = new Animation({CELL_WORLD_SIZE.x + 50.f, CELL_WORLD_SIZE.y + 50.f}, L"InGame/BlockDestroyedSprite/common_block.png", 4, 1, 4);
	destroyedAnim->Stop();
	destroyedAnim->SetEndEvent(bind(&Block::SetActive, this, false));

	HandleAddItem();
}

Block::~Block()
{
	delete rectBody;
	delete texObj;

	delete destroyedAnim;
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

	destroyedAnim->Update();
}

void Block::Render()
{
	if (!isActive) return;

	if (!visible) return;
	
	rectBody->Render();

	if (destroyed)
	{
		texObj->SetData();
		destroyedAnim->Render();

		return;
	}

	texObj->Render();
}

void Block::PlayBushInteraction()
{
	if (currentlyBushing)
		return;

	currentlyBushing = true;
}

bool Block::Move(const UINT& destBoardCoordX, const UINT& destBoardCoordY)
{
	if (!Move(Util::ConvertBoardIdxToWorldPos({ destBoardCoordX, destBoardCoordY })))
		return false;

	BlockManager::SwapBlocks(boardPos, { destBoardCoordX, destBoardCoordY });

	boardPos = { destBoardCoordX, destBoardCoordY };


	return true;
}

bool Block::Move(const Util::Coord& destCoord)
{
	if (!Move(Util::ConvertBoardIdxToWorldPos({ destCoord.x, destCoord.y })))
		return false;

	BlockManager::SwapBlocks(boardPos, destCoord);

	boardPos = destCoord;

	return true;
}

bool Block::Move(Vector2 destination)
{
	if (currentlyMoving)
		return false;
	
	for (const Vector2& balloonPos : Balloon::GetActiveBalloonPositions())
	{
		if (destination == balloonPos)
			return false;
	}
	
	currentlyMoving = true;

	this->destination = destination;

	return true;
}

void Block::ApplyDamage()
{
	if (!isActive)
		return;

	if (!breakable)
		return;

	hp--;

	if (hp <= 0)
	{
		destroyed = true;
		destroyedAnim->Play(false);
		
		if (hidable) // ������ �ִ� ��ü�� visible��� ���ְ� ����
		{
			for (ColliderHolder* owner : rectBody->EnteredPointOwners())
			{
				Character* character = dynamic_cast<Character*>(owner);

				if (character)
				{
					character->SetVisible(true);
					continue;
				}

				Block* b = dynamic_cast<Block*>(owner);

				if (b)
				{
					b->SetVisible(true);
					continue;
				}
			}

			rectBody->EnteredPointOwners().clear();
		}


		if (item) item->Spawn(rectBody->translation);
		
	}
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
	if		(interactTime < 0.1f)	texObj->translation.x =  5.f;
	else if (interactTime < 0.2f)	texObj->translation.x = -5.f;
	else if (interactTime < 0.3f)	texObj->translation.x =  5.f;
	else if (interactTime < 0.4f)	texObj->translation.x = -5.f;
	else
	{
		interactTime = 0.f;
		texObj->translation.x = 0.f;

		currentlyBushing = false;
	}

}

void Block::OnColliderPointEnter(ColliderHolder* owner)
{
	if (hidable) PlayBushInteraction();
}

void Block::OnColliderPointStay(ColliderHolder* owner)
{
	if (destroyed) return;

	if (hidable)
	{
		Character* c = dynamic_cast<Character*>(owner);

		if (c)
		{
			c->SetVisible(false);
			return;
		}

		// Block entered(Movable block)
		Block* b = dynamic_cast<Block*>(owner);
		
		if (b)
		{
			b->SetVisible(false);
			return;
		}

		// Balloon staying
		Balloon* balloon = dynamic_cast<Balloon*>(owner);

		if (balloon)
		{
			if (balloon->Active())
			{
				balloon->SetVisible(false);
				return;
			}

			// balloon�� active���� ���� ���, entererdSet���� ����� ��
			rectBody->EnteredPointOwners().erase(owner);
			return;
		}

	}
}

void Block::OnColliderPointExit(ColliderHolder* owner)
{
	if (hidable)
	{
		PlayBushInteraction();

		Character* c = dynamic_cast<Character*>(owner);

		if (c)
		{
			c->SetVisible(true);
			return;
		}

		Block* b = dynamic_cast<Block*>(owner);

		if (b)
		{
			b->SetVisible(true);
			return;
		}

		Balloon* balloon = dynamic_cast<Balloon*>(owner);

		if (balloon) // ���߿� balloon ������ ���� ������ ������ ���δ°� ��������?
		{
			balloon->SetVisible(true);
			return;
		}
			
	}
}

void Block::OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner)
{
	// Hidable ���� (��ϵ� ���� �ʴ´�)
	if (targetCollider->GetColliderTag() != CHARACTER_PUSH)
	{
		Character* c = dynamic_cast<Character*>(owner);

		if (c)
		{
			if (!breakable) // �� �μ����� ����� ��� ĳ���Ͱ� ��� �����̵� CommonCollision�� ó��
			{
				CollisionUtil::HandleCharacterCommonCollision(rectBody, targetCollider);
				return;
			}
			
			if (c->GetCharacterState() == C_SPACECRAFT) return;
			
			CollisionUtil::HandleCharacterCommonCollision(rectBody, targetCollider);

		}

	}
	else
	{

	}
}

void Block::OnColliderRectStay(ColliderRect* targetCollider, ColliderHolder* owner)
{
	if (movable && targetCollider->GetColliderTag() == CHARACTER_PUSH)
	{
		if (currentlyMoving)
		{
			appliedTime = 0.f;
			return;
		}

		Character* character = dynamic_cast<Character*>(owner);

		if (!character) return;
		
		switch (character->GetCharacterState())
		{
		case C_SPAWN: case C_SPACECRAFT: case C_CAPTURED: case C_RETURN_IDLE: case C_DEAD: return;
		default: break;
		}

		Direction collidedFace = CollisionUtil::GetCollidedDirection(rectBody, targetCollider);

		Vector2 cVelocity = character->GetVelocity();
		Direction cDir = (cVelocity.x > 0) ? DIR_RIGHT	:
						 (cVelocity.x < 0) ? DIR_LEFT	:
						 (cVelocity.y > 0) ? DIR_UP		:
						 (cVelocity.y < 0) ? DIR_DOWN	: DIR_NONE;

		Util::Coord destCoord = boardPos;
		
		switch (cDir)
		{
		case DIR_UP:	destCoord.y += 1; break;
		case DIR_DOWN:	destCoord.y -= 1; break;
		case DIR_LEFT:	destCoord.x -= 1; break;
		case DIR_RIGHT: destCoord.x += 1; break;
		default: break;
		}

		
		// �浹�ϰ� �ִ� ���� ����� ĳ������ �� velocity�� �¹����� �ð��� ����
		// TODO : �÷��̾ destination�� ����� ��
		// + �����̰��� �ϴ� ��鿡 ��ü�� ����� �� + �� ���� ����

		if (!IsPushing(cDir, collidedFace))
		{
			appliedTime = 0.f;
			return;
		}

		if (!BlockManager::IsValidDestCoord(destCoord))
		{
			appliedTime = 0.f;
			return;
		}

		appliedTime += Time::Delta();
		
		// �б� ����
		if (appliedTime >= APPLIED_TIME_LIMIT)
		{
			Move(destCoord);
			appliedTime = 0.f;
		}
	}
}

void Block::OnColliderRectExit(ColliderRect* targetCollider, ColliderHolder* owner)
{
	// Hidable ���� (��ϵ� ���� �ʴ´�)

}


bool Block::IsPushing(const Direction& cDirection, const Direction& collidedFace)
{
	
	switch (collidedFace)
	{
	case DIR_UP:	return (cDirection == DIR_DOWN);
	case DIR_DOWN:  return (cDirection == DIR_UP);
	case DIR_LEFT:  return (cDirection == DIR_RIGHT);
	case DIR_RIGHT: return (cDirection == DIR_LEFT);
	default:
		return false;
	}

}

void Block::HandleAddItem()
{
	if (hidable || !breakable) return;

	//item = (rand() % 2 == 0) ? new ImmediateItem(I_TURTLE) : new ImmediateItem(I_OWL);
	item = new ImmediateItem((ItemName(Util::GetRandom(5, 7))));
	ItemManager::AddItem(item);

	//item = new ConsumableItem(NEEDLE);
	//ItemManager::AddItem(item);

	//if (rand() % 2 != 0) return;


	//// BUBBLE, ROLLER�� ���� �����Ǿ�� ��
	//if (Util::GetRandom(0, 9) < 8) // 80% Ȯ���� Immediate Item ����
	//{
	//	// ���� �Ǹ� ���� ���� �õ�
	//	if (Util::GetRandom(1, 100) == 30) // ���� �Ǹ� ����Ȯ�� 1%
	//	{
	//		item = new ImmediateItem(RED_DEVIL);
	//		ItemManager::AddItem(item);
	//		return;
	//	}
	//	
	//	// 90%�� Ȯ���� Power-up ����
	//	if (Util::GetRandom(0, 9) != 9)
	//	{
	//		// 60%�� Ȯ���� ROLLER�� BUBBLE ����
	//		if (Util::GetRandom(0, 9) < 6)
	//		{
	//			item = new ImmediateItem((ItemName)(rand() % 2));
	//			ItemManager::AddItem(item);
	//			return;
	//		}
	//		else // 40%�� Ȯ���� ������ ����
	//		{
	//			item = new ImmediateItem((ItemName)(Util::GetRandom(2, 4)));
	//			ItemManager::AddItem(item);
	//			return;
	//		}
	//	}
	//	else // 10%�� Ȯ���� Ż �� ����
	//	{
	//		item = new ImmediateItem((ItemName(Util::GetRandom(5, 7))));
	//		ItemManager::AddItem(item);
	//		return;
	//	}
	//} 
	//else  // 20%�� Ȯ���� Consumable ������ ����
	//{
	//	item = new ConsumableItem((ItemName)(Util::GetRandom(8, 10))); 
	//	ItemManager::AddItem(item);
	//}
	


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
