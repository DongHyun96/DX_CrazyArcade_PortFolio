#include "Framework.h"
#include "Player.h"

Player::Player(const CharacterType& cType)
	:Character(cType)
{
	speedLv = 5;
}

Player::~Player()
{
}

void Player::Move()
{
	velocity = Vector2();

	if (KEY_DOWN(VK_LSHIFT))
		speedLv++;

	if (KEY_DOWN('1'))
		mainState = C_SPACECRAFT;
	else if (KEY_DOWN('2'))
		mainState = C_OWL;
	else if (KEY_DOWN('3'))
		mainState = C_TURTLE;
	else if (KEY_DOWN('4'))
		mainState = C_CAPTURED;
	else if (KEY_DOWN('5'))
		mainState = C_IDLE;



	if (KEY_PRESS(VK_LEFT))
	{
		velocity = { -SPEED_BASE * speedLv, 0.f };
	}
	else if (KEY_PRESS(VK_RIGHT))
	{
		velocity = { SPEED_BASE * speedLv, 0.f };
	}
	else if (KEY_PRESS(VK_UP))
	{
		velocity = { 0.f, SPEED_BASE * speedLv };

	}
	else if (KEY_PRESS(VK_DOWN))
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

	if (KEY_DOWN(VK_SPACE))
	{
		Util::Coord deployCoord = GM->GetCollidedMapCellCoord(body->GlobalPosition());
		
		if (GM->GetBalloonManager()->Spawn(deployCoord, this))
		{
			SOUND->Play("BalloonDeploy", 1.f);

			leftBalloonCnt--;
		}
	}
}
