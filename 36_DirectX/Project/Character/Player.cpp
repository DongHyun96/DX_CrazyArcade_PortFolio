#include "Framework.h"
#include "Player.h"

Player::Player(const CharacterType& cType, const PlayerType& playerType)
	:Character(cType, playerType)
{
}

Player::~Player()
{
}

void Player::Move()
{
	velocity = Vector2();

	
	if (KEY_PRESS(GM->P_DIR_KEYCODE[playerType][DIR_LEFT]))
	{
		velocity = { -SPEED_BASE * speedLv, 0.f };
	}
	else if (KEY_PRESS(GM->P_DIR_KEYCODE[playerType][DIR_RIGHT]))
	{
		velocity = { SPEED_BASE * speedLv, 0.f };
	}
	else if (KEY_PRESS(GM->P_DIR_KEYCODE[playerType][DIR_UP]))
	{
		velocity = { 0.f, SPEED_BASE * speedLv };

	}
	else if (KEY_PRESS(GM->P_DIR_KEYCODE[playerType][DIR_DOWN]))
	{
		velocity = { 0.f, -SPEED_BASE * speedLv };
	}

	// 4 way movements 라 noramlize할 필요가 없음
	body->translation += velocity * Time::Delta();
}

void Player::DeployBalloon()
{
	switch (mainState)
		case C_SPAWN: case C_CAPTURED:
		case C_RETURN_IDLE: case C_DEAD: return;

	if (leftBalloonCnt <= 0)
		return;

	if (KEY_DOWN(GM->P_BALLOON_KEYCODE[playerType]))
	{
		Util::Coord deployCoord = GM->GetCollidedMapCellCoord(body->GlobalPosition());
		
		if (GM->GetBalloonManager()->Spawn(deployCoord, this))
		{
			SOUND->Play("BalloonDeploy", 1.f);

			leftBalloonCnt--;
		}
	}
}

void Player::HandleUseConsumableItem()
{
	//?????????????????????????????
	if (playerType == P1 && GetAsyncKeyState(VK_RCONTROL))
		UseConsumableItem();
	else if (playerType == P2 && KEY_DOWN(VK_LCONTROL))
		UseConsumableItem();

	if (KEY_DOWN(GM->P_ITEM_KEYCODE[playerType]))
		UseConsumableItem();
}
