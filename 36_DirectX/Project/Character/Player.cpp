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

	
	if (KEY_PRESS(PM->P_DIR_KEYCODE[playerType][DIR_LEFT]))
	{
		velocity = { -SPEED_BASE * speedLv, 0.f };
	}
	else if (KEY_PRESS(PM->P_DIR_KEYCODE[playerType][DIR_RIGHT]))
	{
		velocity = { SPEED_BASE * speedLv, 0.f };
	}
	else if (KEY_PRESS(PM->P_DIR_KEYCODE[playerType][DIR_UP]))
	{
		velocity = { 0.f, SPEED_BASE * speedLv };
	}
	else if (KEY_PRESS(PM->P_DIR_KEYCODE[playerType][DIR_DOWN]))
	{
		velocity = { 0.f, -SPEED_BASE * speedLv };
	}

	// 4 way movements 라 noramlize할 필요가 없음
	body->translation += velocity * Time::Delta();
}

void Player::DeployBalloon()
{
	switch (mainState)
	{ // 물풍선을 놓지 못할 상황일 때
	case C_SPAWN: case C_CAPTURED: case C_RETURN_IDLE: case C_DEAD: case C_WIN: return;
	}

	// 물풍선 키 입력이 들어오지 않았을 때
	if (!KEY_DOWN(PM->P_BALLOON_KEYCODE[playerType])) return; 

	// 타이머 벌룬이 세팅되어있을 때
	if (!timerBalloons.empty())
	{

		// 타이머 벌룬들을 한번에 터침
		for (TimerBalloon* t_balloon : timerBalloons)
		{
			if (!t_balloon) continue;

			t_balloon->Explode();
		}

		timerBalloons.clear();

		return;
	}

	// 놓을 수 있는 물풍선의 개수가 없을 때
	if (leftBalloonCnt <= 0) return;
	
	Util::Coord deployCoord = GM->GetCollidedMapCellCoord(body->GlobalPosition());
	
	if (GM->GetBalloonManager()->Spawn(deployCoord, this))
	{
		SOUND->Play("BalloonDeploy", 1.f);

		leftBalloonCnt--;
	}
}

void Player::HandleUseConsumableItem()
{
	if (KEY_DOWN(PM->P_ITEM_KEYCODE[playerType]))
		UseConsumableItem();
}
