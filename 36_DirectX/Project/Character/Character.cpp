#include "Framework.h"
#include "Character.h"


Character::Character(const CharacterType& cType, const PlayerType& playerType)
{
	this->playerType = playerType;

	/*Vector2 characterBodySize = { CELL_WORLD_SIZE.x - 30.f, CELL_WORLD_SIZE.y - 30.f };
	Vector2 pushColSize = { CELL_WORLD_SIZE.x - 15.f, CELL_WORLD_SIZE.y - 15.f };*/

	Vector2 characterBodySize = { CELL_WORLD_SIZE.x - 1.f, CELL_WORLD_SIZE.y - 1.f };
	Vector2 pushColSize = { CELL_WORLD_SIZE.x + 10.f, CELL_WORLD_SIZE.y + 10.f };

	body = new ColliderRect(characterBodySize);
	body->SetColliderTag(CHARACTER);

	shadow = new Object({ CELL_WORLD_SIZE.x - 30.f, CELL_WORLD_SIZE.y - 30.f }, L"InGame/Characters/CharacterShadow.png");
	shadow->translation.y -= 25.f;
	shadow->SetColor(1, 1, 1, 0.6f);
	shadow->SetParent(body);
	
	pushCollider = new ColliderRect(pushColSize);
	pushCollider->SetColliderTag(CHARACTER_PUSH);
	pushCollider->SetColor(1, 0, 0);

	pushCollider->SetParent(body);

	actionHandler = CharacterAnimFactory::CreateCharacterAnim(cType, body);
	actionHandler->SetReturnIdleEndEvent(bind(&Character::OnEndReturnToIdle, this));
	actionHandler->SetCapturedEndEvent(bind(&Character::OnCapturedEnd, this));
	actionHandler->SetDeadEndEvent(bind(&Character::OnDeadEnd, this));

	colorBuffer = new ColorBuffer();

	arrow = (playerType == P1) ? new Object(L"InGame/Characters/PlayerArrow/1p.png") :
			(playerType == P2) ? new Object(L"InGame/Characters/PlayerArrow/2p.png") : nullptr;

	if (arrow)
	{
		arrow->scale = { 2.f, 1.5f };
		arrow->translation.y = actionHandler->GetCurActionSize().y * 1.3f;

		arrowYDestMap =
		{
			{false, actionHandler->GetCurActionSize().y * 1.6f},
			{true, actionHandler->GetCurActionSize().y * 1.4f}
		};

		arrow->SetParent(body);
	}

	// 스탯 설정
	InitStat(cType);
	

}

Character::~Character()
{
	delete actionHandler;

	delete body;
	delete pushCollider;

	delete colorBuffer;

	delete shadow;

	if (arrow) delete arrow;

}

void Character::Init()
{
	visible = true;

	colorBuffer->SetData({ 1,1,1,1 });

	velocity *= 0.f;

	mainState = C_SPAWN;

	actionHandler->Init();

	consumableItem = nullptr;

	timerBalloons.clear();

	speedLv = speedLvMin;
	curIdleSpeedLv = speedLv;

	leftBalloonCnt = balloonCntMin;
	streamLv = streamLvMin;

	flicker = 0.f;
	flicked = false;
}

void Character::Update()
{
	body->Update();
	pushCollider->Update();

	body->UpdateZDepthToY();

	shadow->Update();
	
	if (arrow)
	{
		arrowYDestMap =
		{
			{false, actionHandler->GetCurActionSize().y * 1.5f},
			{true, actionHandler->GetCurActionSize().y * 1.2f}
		};

		if (abs(arrow->translation.y - arrowYDestMap[arrowYSwitched]) < 0.99f)
			arrowYSwitched = !arrowYSwitched;
		else arrow->translation.y = Util::Lerp(arrow->translation.y, arrowYDestMap[arrowYSwitched], 0.01f);

		arrow->Update();
	}
	

	actionHandler->Update();
	actionHandler->UpdateAction(mainState, velocity);

	switch (mainState)
	{ 
	case C_IDLE: case C_OWL: case C_TURTLE: case C_CAPTURED:
		break;
	case C_SPACECRAFT: // y Depth 고정시킴
		body->zDepth = -1.f;
		break;
	case C_SPAWN:

		flicker += Time::Delta();

		if (flicker >= 0.05f)
		{
			if (flicked) colorBuffer->SetData({ 1,1,1,1 });
			else colorBuffer->SetData(SPAWN_COLOR);
			
			flicked = !flicked;
			flicker -= 0.05f;
		}

		return;
	case C_RETURN_IDLE: case C_DEAD: case C_WIN:
		return;
	default:
		break;
	}

	Move();
	DeployBalloon();
	HandleUseConsumableItem();

	HandleBoundary();
}

void Character::Render()
{
	if (!visible)
		return;

	if (arrow) arrow->Render();

	colorBuffer->PSSetBuffer(0);

	actionHandler->Render(); // 여기에서 shader 세팅

	shadow->Render();

	body->Render();
	pushCollider->Render();

	Debug();

}

void Character::Debug()
{
	assert(label != "");

	if (ImGui::BeginMenu(label.c_str()))
	{
		ImGui::InputInt("MainState", (int*)&mainState);
		ImGui::EndMenu();
	}

	body->Debug(label);
	actionHandler->Debug("ActionHandler");
}

void Character::SetCharacterState(const CharacterState& state)
{
	//this->mainState = state;
	switch (state)
	{
	case C_IDLE:
		speedLv = curIdleSpeedLv;
		colorBuffer->SetData({ 1,1,1,1 });
		break;
	case C_SPACECRAFT:
		curIdleSpeedLv = speedLv;
		speedLv = SpeedLv::spaceSpeedLv;
		break;
	case C_OWL:
		curIdleSpeedLv = speedLv;
		speedLv = SpeedLv::owlSpeedLv;
		break;
	case C_TURTLE:
		curIdleSpeedLv = speedLv;
		speedLv = SpeedLv::turtleSpeedLv;
		break;
	case C_CAPTURED:
		curIdleSpeedLv = speedLv;
		speedLv = SpeedLv::capturedSpeedLv;
		SOUND->Play("Captured", 1.f);
		break;
	case C_RETURN_IDLE: // 이 때 속도가 0
		if (mainState == C_CAPTURED)
			SOUND->Play("Saved", 1.f);
		speedLv = 0;
		break;
	case C_DEAD:
		SOUND->Play("Die", 0.6f);
		speedLv = 0;
	case C_WIN:
		actionHandler->SetReturnIdleEndEvent(bind(&Character::OnEndReturnToIdle, this));
		break;
	default:
		break;
	}

	this->mainState = state;
}

bool Character::AddLeftBalloonCnt(const UINT& addAmount)
{
	if (leftBalloonCnt >= balloonCntMax) return false;

	leftBalloonCnt += addAmount;

	return true;
}

Direction Character::GetCurFaceDir() const
{
	return actionHandler->GetCurFaceDir();
}

void Character::SetGameOver()
{
	if (mainState == C_DEAD) return;

	if (mainState == C_IDLE || mainState == C_CAPTURED) SetCharacterState(C_WIN);

	if (mainState == C_SPACECRAFT)
	{
		Block* underFeetBlock = GM->GetBlockManager()->GetCoordBlock(GM->GetCollidedMapCellCoord(body->GlobalPosition()));

		if (underFeetBlock) if (underFeetBlock->IsActive()) return;
	}

	if (mainState == C_SPACECRAFT || mainState == C_OWL || mainState == C_TURTLE)
	{
		actionHandler->SetReturnIdleEndEvent(bind(&Character::OnEndReturnToIdleOnGameOver, this));
		SetCharacterState(C_RETURN_IDLE);
	}
}

bool Character::UseConsumableItem()
{
	if (!consumableItem) return false; // 가지고 있는 아이템이 없음
	
	return consumableItem->UseItem(this);
}

bool Character::IncreaseSpeed(bool increaseToMax)
{
	// curIdleSpeed가 현재 저장해놓은 IdleSpeed

	if (curIdleSpeedLv >= speedLvMax) return false;

	curIdleSpeedLv = increaseToMax ? speedLvMax : curIdleSpeedLv + 1;

	if (mainState == C_IDLE) speedLv = curIdleSpeedLv;

	return true;
}

bool Character::IncreaseStreamLv(bool increaseToMax)
{
	if (streamLv >= streamLvMax) return false;
	streamLv = increaseToMax ? streamLvMax : streamLv + 1;
	return true;
}

void Character::HandleBoundary()
{
	if (body->Left() < GM->GetMapL())
		body->translation.x = GM->GetMapL() + body->LocalSize().x * 0.51f;
	if (body->Right() > GM->GetMapR())
		body->translation.x = GM->GetMapR() - body->LocalSize().x * 0.51f;
	if (body->Top() > GM->GetMapT())
		body->translation.y = GM->GetMapT() - body->LocalSize().y * 0.51f;
	if (body->Bottom() < GM->GetMapB())
		body->translation.y = GM->GetMapB() + body->LocalSize().y * 0.51f;
	//else if (body->Bottom() < 0)
}

void Character::InitStat(const CharacterType& cType)
{
	switch (cType)
	{
	case BAZZI:
		speedLvMin = 5;
		speedLvMax = 9;

		balloonCntMin = 1;
		balloonCntMax = 6;

		streamLvMin = 1;
		streamLvMax = 7;
		break;
	case DAO:
		speedLvMin = 5;
		speedLvMax = 7;

		balloonCntMin = 1;
		balloonCntMax = 10;

		streamLvMin = 1;
		streamLvMax = 7;
		break;
	case CAPPI:
		speedLvMin = 4;
		speedLvMax = 8;

		balloonCntMin = 1;
		balloonCntMax = 9;

		streamLvMin = 2;
		streamLvMax = 8;
		break;
	case MARID:
		speedLvMin = 4;
		speedLvMax = 8;

		balloonCntMin = 2;
		balloonCntMax = 9;

		streamLvMin = 1;
		streamLvMax = 6;
		break;
	default:
		break;
	}

	speedLv = speedLvMin;
	curIdleSpeedLv = speedLv;
	
	leftBalloonCnt = balloonCntMin;
	streamLv = streamLvMin;

}
