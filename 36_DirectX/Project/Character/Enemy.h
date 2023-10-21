#pragma once
class Enemy : public Character
{
public:
	Enemy(const CharacterType& cType);
	~Enemy();

private:

	virtual void Move() override;
	virtual void HandleUseConsumableItem() override;
	virtual void DeployBalloon() override;

private:
	stack<Util::Coord> path{};

};
