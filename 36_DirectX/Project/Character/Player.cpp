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

	// 4 way movements �� noramlize�� �ʿ䰡 ����
	body->translation += velocity * Time::Delta();
}

void Player::DeployBalloon()
{
	switch (mainState)
	{ // ��ǳ���� ���� ���� ��Ȳ�� ��
	case C_SPAWN: case C_CAPTURED: case C_RETURN_IDLE: case C_DEAD: case C_WIN: return;
	}

	// ��ǳ�� Ű �Է��� ������ �ʾ��� ��
	if (!KEY_DOWN(PM->P_BALLOON_KEYCODE[playerType])) return; 

	// Ÿ�̸� ������ ���õǾ����� ��
	if (!timerBalloons.empty())
	{

		// Ÿ�̸� ������� �ѹ��� ��ħ
		for (TimerBalloon* t_balloon : timerBalloons)
		{
			if (!t_balloon) continue;

			t_balloon->Explode();
		}

		timerBalloons.clear();

		return;
	}

	// ���� �� �ִ� ��ǳ���� ������ ���� ��
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
