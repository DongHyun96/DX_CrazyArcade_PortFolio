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
	if (KEY_DOWN(VK_F3)) // ��� �缳��
	{
		Util::Coord myCurCoord = GM->GetCollidedMapCellCoord(body->GlobalPosition());
		Util::Coord pCurCoord = GM->GetCollidedMapCellCoord(PM->GetP1()->GetBody()->GlobalPosition());

		path = AStar::GetPath(myCurCoord, pCurCoord, mainState == C_SPACECRAFT);
		int a = 1;
	}
}

void Enemy::HandleUseConsumableItem()
{
}

void Enemy::DeployBalloon()
{
}
