#include "Framework.h"
#include "Character.h"


Character::Character(const CharacterType& cType)
{
	Vector2 characterBodySize = { CELL_WORLD_SIZE.x - 30.f, CELL_WORLD_SIZE.y - 30.f };
	Vector2 pushColSize = { CELL_WORLD_SIZE.x - 15.f, CELL_WORLD_SIZE.y - 15.f };

	//Vector2 characterBodySize = { CELL_WORLD_SIZE.x - 10.f, CELL_WORLD_SIZE.y - 10.f };
	//Vector2 pushColSize = { CELL_WORLD_SIZE.x + 10.f, CELL_WORLD_SIZE.y + 10.f };

	body = new ColliderRect(characterBodySize);
	body->SetColliderTag(CHARACTER);

	pushCollider = new ColliderRect(pushColSize);
	pushCollider->SetColliderTag(CHARACTER_PUSH);
	pushCollider->SetColor(1, 0, 0);

	Util::SetTransformToGameBoard(body, { 7, MAP_ROW - 7 });
	pushCollider->SetParent(body);

	actionHandler = CharacterAnimFactory::CreateCharacterAnim(cType, body);

	colorBuffer = new ColorBuffer();

	// 스탯 설정
	InitStat(cType);
	

}

Character::~Character()
{
	delete actionHandler;

	delete body;
	delete pushCollider;

	delete colorBuffer;

}

void Character::Update()
{
	body->Update();
	pushCollider->Update();

	body->UpdateZDepthToY();

	Move();
	DeployBalloon();

	actionHandler->Update();
	actionHandler->UpdateAction(mainState, velocity);

	switch (mainState)
	{
	case C_SPAWN:
		break;
	case C_IDLE:
		break;
	case C_SPACECRAFT:
		break;
	case C_OWL:
		break;
	case C_TURTLE:
		break;
	case C_CAPTURED: // 상하로 올라갔다 내려갔다 조절

		Util::PlayFloatingEffect(actionHandler->translation.y, captured_yUpdateTime, captured_ySpeed, CAPTURED_Y_UPDATE_TICK);

		break;
	case C_RETURN_IDLE:
		actionHandler->translation.y = 0.f;
		captured_yUpdateTime		= 0.f;
		captured_ySpeed				= 0.f;
		break;
	case C_DEAD:
		break;
	default:
		break;
	}

	HandleBoundary();
}

void Character::Render()
{
	//colorBuffer->SetData(Vector4(1, 0, 1, 1.f));
	if (!visible)
		return;

	colorBuffer->PSSetBuffer(0);

	actionHandler->Render(); // 여기에서 shader 세팅

	body->Render();
	pushCollider->Render();
}

void Character::Debug()
{
	assert(label != "");

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
		break;
	case C_RETURN_IDLE:
		break;
	case C_DEAD:
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
