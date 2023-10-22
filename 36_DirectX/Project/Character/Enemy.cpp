#include "Framework.h"
#include "Enemy.h"



Enemy::Enemy(const CharacterType& cType)
	:Character(cType, COMPUTER)
{
}

Enemy::~Enemy()
{
}

void Enemy::Move()
{
	velocity = Vector2();

	if (KEY_DOWN(VK_F3)) // ��� �缳��
	{
		Util::Coord pCurCoord = GM->GetCollidedMapCellCoord(PM->GetP1()->GetBody()->GlobalPosition());
		UpdatePath(pCurCoord);
	}

	if (path.empty())
	{
		//Util::Coord pCurCoord = GM->GetCollidedMapCellCoord(PM->GetP1()->GetBody()->GlobalPosition());
		//UpdatePath(pCurCoord);
		return;
	}

	Vector2 destination = Util::ConvertBoardIdxToWorldPos(path.top());
	Vector2 dir = destination - body->translation;

	if (dir.Length() < 1.f) // destination reached�� �Ǵ� -> ���⼭ ��� �缳�� Ʈ���Ű� �����ؾ��� & path�� ����� ���� �ѹ� �����ؾ� ��
	{
		body->translation = destination;
		path.pop();
	}
	else
	{
		velocity = dir.GetNormal() * SPEED_BASE * speedLv;
		body->translation += velocity * Time::Delta();
	}
	
}

void Enemy::HandleUseConsumableItem()
{
}

void Enemy::DeployBalloon()
{
}

void Enemy::UpdatePath(const Util::Coord& dest)
{
	Util::Coord myCurCoord = GM->GetCollidedMapCellCoord(body->GlobalPosition());

	path = AStar::GetPath(myCurCoord, dest, mainState == C_SPACECRAFT);
}

