#pragma once
class Player : public Character
{
public:
	Player(const CharacterType& cType, const PlayerType& playerType);
	~Player();

	virtual void Move() override;

private:

	virtual void DeployBalloon() override;

	virtual void HandleUseConsumableItem() override;

};
