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
		
		if (hidable) // 숨겨져 있는 물체들 visible모두 켜주고 해제
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

			// balloon이 active하지 않은 경우, entererdSet에서 빼줘야 함
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

		if (balloon) // 나중에 balloon 발차기 같은 아이템 때문에 놔두는게 나을지도?
		{
			balloon->SetVisible(true);
			return;
		}
			
	}
}

void Block::OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner)
{
	// Hidable 배제 (등록도 하지 않는다)
	if (targetCollider->GetColliderTag() != CHARACTER_PUSH)
	{
		Character* c = dynamic_cast<Character*>(owner);

		if (c)
		{
			if (!breakable) // 안 부서지는 블록의 경우 캐릭터가 어느 상태이든 CommonCollision을 처리
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

		
		// 충돌하고 있는 면의 방향과 캐릭터의 현 velocity가 맞물려야 시간을 더함
		// TODO : 플레이어도 destination에 없어야 함
		// + 움직이고자 하는 방면에 물체가 없어야 함 + 맵 범위 판정

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
		
		// 밀기 만족
		if (appliedTime >= APPLIED_TIME_LIMIT)
		{
			Move(destCoord);
			appliedTime = 0.f;
		}
	}
}

void Block::OnColliderRectExit(ColliderRect* targetCollider, ColliderHolder* owner)
{
	// Hidable 배제 (등록도 하지 않는다)

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


	//// BUBBLE, ROLLER가 많이 스폰되어야 함
	//if (Util::GetRandom(0, 9) < 8) // 80% 확률로 Immediate Item 스폰
	//{
	//	// 붉은 악마 먼저 스폰 시도
	//	if (Util::GetRandom(1, 100) == 30) // 붉은 악마 스폰확률 1%
	//	{
	//		item = new ImmediateItem(RED_DEVIL);
	//		ItemManager::AddItem(item);
	//		return;
	//	}
	//	
	//	// 90%의 확률로 Power-up 스폰
	//	if (Util::GetRandom(0, 9) != 9)
	//	{
	//		// 60%의 확률로 ROLLER나 BUBBLE 스폰
	//		if (Util::GetRandom(0, 9) < 6)
	//		{
	//			item = new ImmediateItem((ItemName)(rand() % 2));
	//			ItemManager::AddItem(item);
	//			return;
	//		}
	//		else // 40%의 확률로 나머지 스폰
	//		{
	//			item = new ImmediateItem((ItemName)(Util::GetRandom(2, 4)));
	//			ItemManager::AddItem(item);
	//			return;
	//		}
	//	}
	//	else // 10%의 확률로 탈 것 스폰
	//	{
	//		item = new ImmediateItem((ItemName(Util::GetRandom(5, 7))));
	//		ItemManager::AddItem(item);
	//		return;
	//	}
	//} 
	//else  // 20%의 확률로 Consumable 아이템 스폰
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
