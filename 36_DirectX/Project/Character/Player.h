#pragma once

/*
CONCRETE CLASS
User input�� ���� control�� ĳ����
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
