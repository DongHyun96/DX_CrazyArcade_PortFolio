#pragma once

/*
CONCRETE CLASS
User input에 의해 control될 캐릭터
*/
class Player : public Character
{
public:
	Player(const CharacterType& cType, const PlayerType& playerType);
	~Player();

	void Move() override;

private:

	void DeployBalloon() override;

	void HandleUseConsumableItem() override;

};
