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

	// ½ºÅÈ ¼³Á¤
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

	HandleBoundary();
}

void Character::Render()
{
	//colorBuffer->SetData(Vector4(1, 0, 1, 1.f));
	if (!visible)
		return;

	colorBuffer->PSSetBuffer(0);

	actionHandler->Render();

	body->Render();
	pushCollider->Render();
}

void Character::Debug()
{
	assert(label != "");

	body->Debug(label);
}

void Character::AddLeftBalloonCnt(const UINT& addAmount)
{
	if (leftBalloonCnt >= balloonCntMax) return;

	leftBalloonCnt += addAmount;
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

	//speedLv = speedLvMin;
	//leftBalloonCnt = balloonCntMin;
	//streamLv = streamLvMin;

	speedLv = speedLvMin;
	leftBalloonCnt = 6;
	streamLv = streamLvMax;
}
